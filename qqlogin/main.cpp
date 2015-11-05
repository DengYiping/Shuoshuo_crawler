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

int main(int argc, const char * argv[]) {
  // insert code here...
  curl_global_init(CURL_GLOBAL_ALL);
  mongo::client::GlobalInstance mongoguard;
  qqlogin::QQ_info new_qq(std::string("649899819"), std::string("@iEWIg1Cdk"));
  fetch::Fetcher new_fetcher(new_qq);
  std::string qq_num = "7896178";
  auto msglist = new_fetcher.parsed_json(qq_num)["msglist"][0];
  mongo::DBClientConnection client;
  try{
    client.connect("localhost");
  } catch(const mongo::DBException &e ){
    std::cerr<< e.what() << std::endl;
    goto error_cleanup;
  }
  std::cout<<msglist.toStyledString()<<std::endl;
  
error_cleanup:
  curl_global_cleanup();
  return EXIT_SUCCESS;
}
