#ifndef __TLV_HPP__
#define __TLV_HPP__

#include <cstdint>
#include <vector>
#include <string>
using std::string;


enum TaskType
{
    TASK_TYPE_LOGIN_SECTION1 = 1, // 用户登录第一阶段
    TASK_TYPE_LOGIN_SECTION1_RESP_OK, // 用户登录第一阶段响应成功
    TASK_TYPE_LOGIN_SECTION1_RESP_ERROR, // 用户登录第一阶段响应错误
    TASK_TYPE_LOGIN_SECTION2, // 用户登录第二阶段
    TASK_TYPE_LOGIN_SECTION2_RESP_OK, // 用户登录第二阶段响应成功
    TASK_TYPE_LOGIN_SECTION2_RESP_ERROR, // 用户登录第二阶段响应错误
    TASK_TYPE_LOGIN_SUCCESSED,  // 用户登录成功

};

struct TLV
{
    int type;
    int length;
    char data[1024];
};

struct Packet
{
    int type;
    int length;
    string msg;
};



#endif // __TLV_HPP__

