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
    long long g_tk;
    long long hash = 5381;
    auto len = skey.length();
    for(int i = 0; i < len; ++i)
    {
      hash += (hash<<5) + (int)skey[i];
    }
    g_tk = hash & 0x7fffffff;
    g_tk_str = std::to_string(g_tk);
  }
  
  QQ_info::QQ_info(std::string qq_num, std::string qq_skey){
    skey = qq_skey;
    qq_number = qq_num;
    calculate_g_tk();
  }
  
  std::string QQ_info::get_cookie() const{
    std::string cookie;
    std::string uin = "uin=o0" + qq_number + "; ";
    std::string cookie_skey = "skey=" + skey + "; ";
    cookie = uin + cookie_skey;
    return cookie;
  }
  
  std::string QQ_info::get_url(std::string qq_num) const{
    const std::string first("taotao.qq.com/cgi-bin/emotion_cgi_msglist_v6?uin=");
    const std::string middle("&num=2&replynum=100&format=jsonp&g_tk=");
    std::string final = first + qq_num + middle + g_tk_str;
    return final;
  }
  
  
}
