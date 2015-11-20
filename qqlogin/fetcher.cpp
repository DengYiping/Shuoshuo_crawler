//
//  fetcher.cpp
//  qqlogin
//
//  Created by Scott Deng on 11/3/15.
//  Copyright © 2015 github. All rights reserved.
//

#include "fetcher.hpp"
#include <iostream>
#include <utility>

namespace fetch{
  static Bloom_filer<1024*1024*1024> qq_filter;
  
  size_t curl_writer(char *data, size_t size, size_t nmemb, std::string *writerData)
  {
    auto realsize = size * nmemb;
    if (realsize <= 0) return 0;
    writerData->append(data);
    return realsize;
  } //curl writer for data buffer
  
  Fetcher::Fetcher(const qqlogin::QQ_info& qq, threadtool::Threadsafe_queue<std::string>* qq_que){
    logined_qq = qq;
    cookie = qq.get_cookie();
    
    match_json = "^_Callback\\((.*)\\);$";//here is the regex pattern
    qq_queue = qq_que;
    match_qq = "\"uin\": ?(\\d+)(.*)"; //here is the regex pattern
    
    CURLcode code;
    easyhandle = curl_easy_init();
    if(!easyhandle) goto errors;
    
    code = curl_easy_setopt(easyhandle, CURLOPT_TIMEOUT,5L);
    if(code != CURLE_OK) goto errors;
    
    //code = curl_easy_setopt(easyhandle, CURLOPT_USERAGENT,"Mozilla/5.0 (SymbianOS/9.4; Series60/5.0 Nokia5233/21.1.004; Profile/MIDP-2.1 Configuration/CLDC-1.1 ) AppleWebKit/525 (KHTML, like Gecko) Version/3.0 //BrowserNG/7.2.5.2 3gpp-gba");
    //if(code != CURLE_OK) goto errors;
    
    //useragent
    
    code = curl_easy_setopt(easyhandle, CURLOPT_COOKIE, cookie.c_str());
    if(code != CURLE_OK) goto errors;
    //cookie: third argument as char*
    
    code = curl_easy_setopt(easyhandle,CURLOPT_FOLLOWLOCATION, 1L);
    if(code != CURLE_OK) goto errors;
    
    code = curl_easy_setopt(easyhandle, CURLOPT_VERBOSE,0L);
    if(code != CURLE_OK) goto errors;
    //verbose mode disabled: enable if in debug
    
    code = curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, curl_writer);
    if(code != CURLE_OK) goto errors;
    
    //pass writer function
    code = curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, &data_buffer);
    if(code != CURLE_OK) goto errors;
    
    return;
  errors:
    fprintf(stderr, "error in initialize curl");
    return;
  }
  
  Fetcher::~Fetcher(){
    curl_easy_cleanup(easyhandle);
  }
  
  std::string& Fetcher::get(std::string& qq_num){
    data_buffer = "";
    std::string url = logined_qq.get_url(qq_num);
    //std::cout<<url<<std::endl;
    auto code = curl_easy_setopt(easyhandle, CURLOPT_URL, url.c_str());
    if(code != CURLE_OK) fprintf(stderr, "error in changing url");
    curl_easy_perform(easyhandle);
    return this->data_buffer;
  }
  
  std::string Fetcher::get_json(std::string &qq_num){
    get(qq_num);
    boost::smatch substrings;
    boost::regex_match(data_buffer,substrings,match_json);
    return substrings[1];
  }
  
  Json::Value Fetcher::parsed_json(std::string& qq_num){
    Json::Value root;
    Json::Reader reader;
    
    get(qq_num); //get raw data from Tencent server
    boost::smatch substrings;
    std::string json_string;
    bool isSuccess = boost::regex_match(data_buffer,substrings,match_json);
    if (isSuccess == true){
      json_string = substrings[1];
      bool parsedSuccess = reader.parse(json_string, root);
      if(! parsedSuccess){;
        fprintf(stderr, "error in parsing the json document");
      } //the document is parsable, then iterate through the whole structure to find "uin"
      
      else{
        boost::smatch qqs;
        while (boost::regex_search (json_string,qqs,match_qq)) {
          std::string qq_nume = qqs[1];
          if(!qq_filter.check_add(qq_nume)) { //bloom filter
            qq_queue->push(qq_nume); //push into the queue
            printf("new qq:%s\n",qq_nume.c_str()); //print out info
          }
          json_string = qqs[2].str();
        }
      }//if the string is parsable
    }//if the string is not null
    else {
      reader.parse(std::string(""), root);
      printf("the return value has some error\n");
    } //still parse it.
    return root;
  }

  
  mongo::BSONObj Shuoshuo::toBSON() const{
    mongo::BSONObj bson;
    if(is_forwarding == false){
      bson = mongo::BSONObjBuilder().append("uid", uid).append("name",name).append("time",time).append("content",content).obj();
    }
    else{
      bson = mongo::BSONObjBuilder().append("uid", uid).append("name",name).append("time",time).append("content",content).append("forward",forwarding_content).obj();
    }
    
    return bson;
  }
  
  Shuoshuo::Shuoshuo(Json::Value& raw){
    name = raw["name"].asString();
    uid = raw["uin"].asLargestInt();
    content = raw["content"].asString();
    time = mongo::Date_t( (raw["created_time"].asLargestInt()) * 1000 );
    auto forward_json = raw["rt_con"]["content"];
    if(forward_json.empty() == false){
      forwarding_content = forward_json.asString();
      is_forwarding = true;
    }
    else{
      forwarding_content = "";
      is_forwarding = false;
    }
  }
  
  
}
