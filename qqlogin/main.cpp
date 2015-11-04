//
//  main.cpp
//  qqlogin
//
//  Created by Scott Deng on 9/12/15.
//  Copyright (c) 2015 github. All rights reserved.
//

#include <iostream>
#include "qqlogin.h"

int main(int argc, const char * argv[]) {
  // insert code here...
  qqlogin::QQ_info new_qq(std::string("649899819"), std::string("@jeUEVJpTW"), std::string("91840aa693da1e6b"));
  std::cout<<new_qq.get_g_tk()<<std::endl;
  std::cout<<new_qq.get_cookie()<<std::endl;
  return 0;
}
