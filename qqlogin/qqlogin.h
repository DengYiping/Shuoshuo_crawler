//
//  qqlogin.h
//  qqlogin
//
//  Created by Scott Deng on 9/13/15.
//  Copyright (c) 2015 github. All rights reserved.
//

#ifndef __qqlogin__qqlogin__
#define __qqlogin__qqlogin__

#include <stdio.h>
#include <curl/curl.h>
#include <string>

namespace qqlogin{
  class QQ_info{
  private:
    std::string qq_number;
    std::string skey;
    long long g_tk;
    std::string g_tk_str;
    std::string server_addr;
    void calculate_g_tk();
  public:
    explicit QQ_info(std::string qq_num, std::string qq_skey, std::string pt_server); //constrcutor
    std::string get_cookie(); //get the cookies
    std::string get_url(std::string qq_num);
    std::string get_qq_number() { return qq_number;} //return the corrent login qq_number
  }; //class QQ_login --get the login info, including cookie
  
  
}

#endif /* defined(__qqlogin__qqlogin__) */
