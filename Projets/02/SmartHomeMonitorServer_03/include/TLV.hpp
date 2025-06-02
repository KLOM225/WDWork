#ifndef __TLV_HPP__
#define __TLV_HPP__

#include <cstdint>
#include <vector>
#include <string>
using std::string;


enum TaskType
{
    TASK_TYPE_LOGIN_SECTION1 = 1,
    TASK_TYPE_LOGIN_SECTION1_RESP_OK,
    TASK_TYPE_LOGIN_SECTION1_RESP_ERROR, 
    TASK_TYPE_LOGIN_SECTION2,
    TASK_TYPE_LOGIN_SECTION2_RESP_OK,
    TASK_TYPE_LOGIN_SECTION2_RESP_ERROR,
    
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

