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
#include <string>

namespace qqlogin{
  class QQ_info{
  private:
    std::string qq_number;
    std::string skey;
    std::string g_tk_str;
    void calculate_g_tk();
  public:
    explicit QQ_info(std::string qq_num, std::string qq_skey); //constrcutor
    QQ_info() {}
    QQ_info& operator = (const QQ_info& second) {
      qq_number = second.qq_number;
      skey = second.skey;
      g_tk_str = second.g_tk_str;
      return *this;
    }
    
    std::string get_cookie() const; //get the cookies
    std::string get_url(std::string qq_num) const;
    std::string get_qq_number() const { return qq_number;} //return the corrent login qq_number
    std::string  get_g_tk() const {return g_tk_str;}
  }; //class QQ_login --get the login info, including cookie
  
  
}

#endif /* defined(__qqlogin__qqlogin__) */
