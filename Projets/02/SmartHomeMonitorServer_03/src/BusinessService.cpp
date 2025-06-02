#include "BusinessService.hpp"
#include "Mylogger.hpp"

//#include <QCryptographicHash> // 使用Qt加密库保持一致性

#include <string>
#include <iostream>
#include <random>
#include <memory>
#include <cstring>

using std::cout;
using std::endl;

// 该函数运行在计算线程
void UserLoginSection::process1()
{
    cout << "login section 1 is processing" << endl;
    if (_packet.type == TASK_TYPE_LOGIN_SECTION1)
    {
        string username = _packet.msg;
        LogDebug("Received login1 request for user: %s\n", username.c_str());
        // 检查用户是否存在
        if (_mysql->user_exists(username.c_str()))
        {
            string salt = _mysql->get_setting(username);

            if (!salt.empty())
            {
                LogDebug("Existing user salt: %s\n", salt.c_str());

                TLV tlv;
                tlv.type = TASK_TYPE_LOGIN_SECTION1_RESP_OK;
                tlv.length = salt.length();
                strncpy(tlv.data, salt.c_str(), tlv.length);
                cout << "Type: " << tlv.type << ", Length: " << tlv.length << ", Data: " << tlv.data << endl;
                _conn->sendInLoop(tlv);
            }
            else
            {
                LogError("Failed to get salt for user: %s", username.c_str());
                
                TLV tlv;
                tlv.type = TASK_TYPE_LOGIN_SECTION1_RESP_ERROR;
                tlv.length = 0;
                _conn->sendInLoop(tlv);
            }
        }
        else
        {
            // 用户不存在时生成安全盐值
            LogDebug("User not found: %s", username.c_str());
            
            string salt = generateSecureSalt(16); // 生成16字节的安全盐值
            
            // 存储新用户信息（密码留空，等待第二阶段验证）
            if (_mysql->add_user(username, salt, ""))
            {
                LogDebug("New user placeholder created");
                
                TLV tlv;
                tlv.type = TASK_TYPE_LOGIN_SECTION1_RESP_OK;
                tlv.length = salt.length();
                strncpy(tlv.data, salt.c_str(), tlv.length);
                _conn->sendInLoop(tlv);
            }
            else
            {
                LogError("Failed to create user placeholder: %s", username.c_str());
                
                TLV tlv;
                tlv.type = TASK_TYPE_LOGIN_SECTION1_RESP_ERROR;
                tlv.length = 0;
                _conn->sendInLoop(tlv);
            }
        }
    }
}

void UserLoginSection::process2()
{
    cout << "login section 2 is processing" << endl;
    LogDebug("Received login2 request for user: %s\n", _packet.msg.c_str());
    if (_packet.type == TASK_TYPE_LOGIN_SECTION2)
    {
        size_t pos = _packet.msg.find_first_of('$');
        
        if (pos == string::npos)
        {
            cout << "Invalid packet format" << endl;
            sendAuthResponse(false);
            return;
        }
        
        string username = _packet.msg.substr(0, pos);
        string client_encrypted = _packet.msg.substr(pos + 1);
        
        // 获取服务器存储的盐值和加密密码
        string salt = _mysql->get_setting(username);
        string db_encrypted = _mysql->get_encrypt(username);
        
        TLV response;
        
        // 新用户注册流程
        if (db_encrypted.empty())
        {
            // 验证密码有效性（示例：至少6位）
            if (client_encrypted.length() < 12) { // SHA256结果通常64字符
                LogDebug("Invalid password format for new user");
                sendAuthResponse(false);
                return;
            }
            
            // 更新用户密码
            if (_mysql->update_user_credentials(username, salt, client_encrypted))
            {
                LogDebug("New user registered: %s", username.c_str());
                sendAuthResponse(true);
            }
            else
            {
                LogError("Failed to register new user: %s", username.c_str());
                sendAuthResponse(false);
            }
        }
        // 现有用户登录验证
        else
        {
            // 在服务器端重新计算加密结果进行验证
            //string server_encrypted = encryptPassword("", salt); // 此处需要真实密码
            
            /*
            实际实现应该：
            1. 从客户端获取明文密码（安全通道传输）
            2. 在服务器端进行加密
            3. 与数据库存储值比较
            
            当前设计需要在客户端-服务器协议中添加密码传输步骤
            */
            
            if (db_encrypted == client_encrypted)
            {
                LogDebug("User %s logged in successfully", username.c_str());
                //sendAuthResponse(true);
                    
                TLV tlv;
                tlv.type = 5;//用户登录成功
                tlv.length = 1;
                strncpy(tlv.data, "0", tlv.length);
                _conn->sendInLoop(tlv);
            }
            else
            {
                LogDebug("Login failed for user: %s", username.c_str());
                sendAuthResponse(false);
            }
        }
    }
}

void UserLoginSection::sendAuthResponse(bool success)
{
    TLV tlv;
    tlv.type = success ? TASK_TYPE_LOGIN_SECTION2_RESP_OK : TASK_TYPE_LOGIN_SECTION2_RESP_ERROR;
    tlv.length = 0;
    _conn->sendInLoop(tlv);
}

string UserLoginSection::generateSecureSalt(int length)
{
    const char alphanum[] = 
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);
    
    string salt;
    salt.reserve(length);
    
    for (int i = 0; i < length; ++i) {
        salt += alphanum[dis(gen)];
    }
    
    return salt;
}

// string UserLoginSection::encryptPassword(const string& password, const string& salt)
// {
//     QByteArray data = QByteArray::fromStdString(salt + password);
//     QByteArray hash = QCryptographicHash::hash(data, QCryptographicHash::Sha256);
//     return hash.toHex().toStdString();
//}