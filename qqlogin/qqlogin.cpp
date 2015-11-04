//
//  qqlogin.cpp
//  qqlogin
//
//  Created by Scott Deng on 9/13/15.
//  Copyright (c) 2015 github. All rights reserved.
//

#include "qqlogin.h"
#include <json/json.h>
namespace qqlogin{
  //----------class QQ_info
  void QQ_info::calculate_g_tk(){
    long long hash = 5381;
    auto len = skey.length();
    for(int i = 0; i < len; ++i)
    {
      hash += (hash<<5) + (int)skey[i];
    }
    g_tk = hash & 0x7fffffff;
  }
  
  QQ_info::QQ_info(std::string qq_num, std::string qq_skey, std::string pt_server){
    skey = qq_skey;
    qq_number = qq_num;
    server_addr = pt_server;
    calculate_g_tk();
    g_tk_str = std::to_string(g_tk);
  }
  
  std::string QQ_info::get_cookie(){
    std::string cookie;
    std::string o_cookie = "o_cookie=" + qq_number +"; ";
    std::string ptui_loginuin = "ptui_loginuin=" + qq_number +"; ";
    std::string pt2gguin = "pt2gguin=o0" + qq_number + "; ";
    std::string uin = "uin=o0" + qq_number + "; ";
    std::string cookie_skey = "skey=" + skey + "; ";
    std::string pt_serverip = "pt_serverip=" + server_addr + "; ";
    cookie = o_cookie + pt_serverip + ptui_loginuin + pt2gguin + uin + cookie_skey;
    return cookie;
  }
  
}
