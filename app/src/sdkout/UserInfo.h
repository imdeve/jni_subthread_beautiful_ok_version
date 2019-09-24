//
// Created by Administrator on 2019/9/23.
//

#ifndef POOLENV_USERINFO_H
#define POOLENV_USERINFO_H


#include "JNIOjbectAccessor.h"

class UserInfo : public JNIOjbectAccessor{
private:
    std::string account;//用户账号ID
    std::string nick;//用户昵称
    std::string avatar;//用户头像
    std::string sign;//用户签名
    std::string email;//邮箱地址
    std::string birth;//用户生日
    std::string mobile;//手机号 mobile
    std::string ex;//JSON格式扩展字段
    int gender;//用户性别,取值范围如下: Unknow(0) <未知>  Male(1) <男性> Female(2) <女性>
    int64_t createat;//创建时间
    int64_t motifyat;// 最后更新时间
};


#endif //POOLENV_USERINFO_H
