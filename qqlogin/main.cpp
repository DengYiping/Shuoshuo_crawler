//
//  main.cpp
//  qqlogin
//
//  Created by Scott Deng on 9/12/15.
//  Copyright (c) 2015 github. All rights reserved.
//

#include <iostream>
#include "qqlogin.h"
#include "fetcher.hpp"
#include "threadtool.h"
#include <regex>
void thread_main(threadtool::Threadsafe_queue<std::string>* qq_queue, std::string* qq, std::string* skey);
int main(int argc, const char * argv[]) {
  // insert code here...
  curl_global_init(CURL_GLOBAL_ALL);
  mongo::client::GlobalInstance mongoguard;
  threadtool::Threadsafe_queue<std::string>* qq_queue = new threadtool::Threadsafe_queue<std::string>;
  
  std::string start_qq;
  std::string session_qq;
  std::string session_skey;
  
  std::cout<<"Please enter the initial qq number to crawling"<<std::endl;
  std::cin>>start_qq;
  

  std::cout<<"Please enter the qq number in order to crawl"<<std::endl;
  std::cin>>session_qq;
  std::cout<<"Please enter the skey in order to crawl"<<std::endl;
  std::cin>>session_skey;
  
  
  qq_queue->push(start_qq);
  
  for(int i = 0; i < 30; i++){
    std::thread new_thread(thread_main,qq_queue, &session_qq, &session_skey);
    new_thread.detach();
  }
  std::thread new_thread(thread_main,qq_queue, &session_qq, &session_skey);
  new_thread.join();
  
error_cleanup:
  curl_global_cleanup();
  return EXIT_SUCCESS;
}

void thread_main(threadtool::Threadsafe_queue<std::string>* qq_queue, std::string* qq, std::string*skey){
  
  mongo::DBClientConnection client;

  client.connect("localhost");
  printf("successfully connected to the database");
  qqlogin::QQ_info new_qq(*qq, *skey);
  fetch::Fetcher new_fetcher(new_qq, qq_queue);
  while(1){
    auto it = new_fetcher.parsed_json(*(qq_queue->wait_pop()))["msglist"][0];
    if (it.empty() == 0){
      fetch::Shuoshuo new_shuoshuo(it);
      auto it2 = new_shuoshuo.toBSON();
      printf("new data arrived");
      client.insert("dbs.qq", it2);
      printf("new data has been inserted to the database");
    }
  }
}