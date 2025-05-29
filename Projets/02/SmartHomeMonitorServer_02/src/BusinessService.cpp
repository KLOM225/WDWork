#include "BusinessService.hpp"
#include "Mylogger.hpp"


#include <shadow.h>
#include <string.h>

#include <iostream>

using std::cout;
using std::endl;

// 该函数运行在计算线程
void UserLoginSection1::process()
{
    cout << "login section 1 is processing" << endl;
    // 执行用户登录的阶段1操作
    if (_packet.type == TASK_TYPE_LOGIN_SECTION1)
    {
        // 消息内容为用户名
        string username = _packet.msg;
        _mysql.connect(); // 确保数据库连接已建立
        
        // 检查用户是否存在
        if (_mysql.user_exists(username.c_str()))
        {
            // 用户存在：生成随机字符串作为盐值
            char *sp = GenRandomString(username.length());

            // 获取要发送给对端的setting（盐值）
            string setting;
            getSetting(setting, sp);
            free(sp); // 释放动态分配的内存
            // 打印调试信息
            LogDebug("Existing user setting: %s\n", setting.c_str());

            // 构造TLV，发送给对端（成功）
            TLV tlv;
            tlv.type = TASK_TYPE_LOGIN_SECTION1_RESP_OK;
            tlv.length = setting.length();
            strncpy(tlv.data, setting.c_str(), tlv.length);
            _conn->sendInLoop(tlv);
        }
        else
        {
            // 用户不存在时自动创建
            LogDebug("User not found, creating new user: %s", username.c_str());

            // 1. 生成随机字符串作为盐值
            char *sp = GenRandomString(username.length());

            // 2. 获取setting格式的盐值
            string setting;
            getSetting(setting, sp);
            LogDebug("New user setting: %s\n", setting.c_str());

            // 3. 创建新用户（设置加密密文为空，后续阶段补充）
            if (_mysql.add_user(username, setting, ""))
            {
                LogDebug("New user created successfully");

                // 4. 发送盐值给客户端（与现有用户相同流程）
                TLV tlv;
                tlv.type = TASK_TYPE_LOGIN_SECTION1_RESP_OK;
                tlv.length = setting.length();
                strncpy(tlv.data, setting.c_str(), tlv.length);
                _conn->sendInLoop(tlv);
            }
            else
            {
                // 用户创建失败处理
                LogError("Failed to create new user: %s", username.c_str());

                TLV tlv;
                tlv.type = TASK_TYPE_LOGIN_SECTION1_RESP_ERROR;
                tlv.length = 0;
                _conn->sendInLoop(tlv);
            }
        }
    }
}

void UserLoginSection1::getSetting(string &s, const char *passwd)
{
    int i, j;
    // 取出salt,i 记录密码字符下标，j记录$出现次数
    for (i = 0, j = 0; passwd[i] && j != 4; ++i)
    {
        if (passwd[i] == '$')
            ++j;
    }
    char buff[128] = {0};
    strncpy(buff, passwd, i);
    // 拷贝到s中
    s.assign(buff, i);
}

void UserLoginSection2::process()
{
    cout << "login section 2 is processing" << endl;
    // 执行用户登录的阶段2操作
    if (_packet.type == TASK_TYPE_LOGIN_SECTION2)
    {
    }


}

char *UserLoginSection1::GenRandomString(int length)
{
    int flag, i;
    char *string;
    srand((unsigned)time(NULL));
    if ((string = (char *)malloc(length)) == NULL)
    {
        printf("malloc failed!flag:14\n");
        return NULL;
    }
    for (i = 0; i < (length + 1); i++)
    {
        flag = rand() % 3;
        switch (flag)
        {
        case 0:
            string[i] = 'A' + rand() % 26;
            break;
        case 1:
            string[i] = 'a' + rand() % 26;
            break;
        case 2:
            string[i] = '0' + rand() % 10;
            break;
        default:
            string[i] = 'x';
            break;
        }
    }
    string[length] = '\0';
    return string;
}