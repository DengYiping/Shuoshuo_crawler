//
//  fetcher.hpp
//  qqlogin
//
//  Created by Scott Deng on 11/3/15.
//  Copyright © 2015 github. All rights reserved.
//

#ifndef fetcher_hpp
#define fetcher_hpp

#include <stdio.h>
#include <curl/curl.h>
#include "qqlogin.h"
#include <regex>
#include <json/json.h>
#include <functional>

/*
 header for MySQL
 */
#include <mutex>
#include "threadtool.h"
//mongodb header
namespace fetch{
  class Fetcher{
  private:
    qqlogin::QQ_info logined_qq;
    CURL *easyhandle; //handle for curl
    std::string data_buffer; //data buffer for curl
    std::string cookie;
    std::regex match_json;
    threadtool::Threadsafe_queue<std::string>* qq_queue;
    std::regex match_qq;
  public:
    Fetcher(const qqlogin::QQ_info& qq, threadtool::Threadsafe_queue<std::string>* qq_queue);
    ~Fetcher();
    std::string& get(std::string& qq_num);
    std::string get_json(std::string& qq_num);
    Json::Value parsed_json(std::string& qq_num);
  };
  
  
  
  template<size_t filter_size>class Bloom_filer{
  private:
    std::hash<std::string> string_hash;
    std::bitset<filter_size> filter_set;
    mutable std::mutex mtx;
    inline long long hash1(std::string& str){return string_hash(str)%filter_size;}
    inline long long hash2(std::string& str){return string_hash(str+"1")%filter_size;}
    inline long long hash3(std::string& str){return string_hash(str+"q")%filter_size;}
    inline long long hash4(std::string& str){return string_hash(str+"$")%filter_size;}
  public:
    inline bool check_add(std::string& str){
      std::lock_guard<std::mutex> locker(mtx);
      if(filter_set[hash1(str)] == 1 && filter_set[hash2(str)] == 1 && filter_set[hash3(str)] == 1 && filter_set[hash4(str)] == 1) return true;
      else{
        filter_set[hash1(str)] = 1;
        filter_set[hash2(str)] = 1;
        filter_set[hash3(str)] = 1;
        filter_set[hash4(str)] = 1;
        return false;
      }
    }
    inline bool check(std::string& str){
      std::lock_guard<std::mutex> locker(mtx);
      if(filter_set[hash1(str)] == 1 && filter_set[hash2(str)] == 1 && filter_set[hash3(str)] == 1 && filter_set[hash4(str)] == 1) return true;
      else{
        return false;
      }
    }
  }; //simple bloomfilter, not threadsafe
  
  
  
  class Shuoshuo{
  private:
    long long uid;
    std::string name;
    std::string content;
    //time structure for MySQL
    bool is_forwarding;
    std::string forwarding_content;
  public:
    Shuoshuo(Json::Value& raw);
    //Return insert data structure for MySQL
    
  }; // Shushu's data structure
}
#endif /* fetcher_hpp */
