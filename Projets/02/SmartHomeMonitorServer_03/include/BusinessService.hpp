#ifndef __BUSINESSSERVICE_HPP__
#define __BUSINESSSERVICE_HPP__

#include "TLV.hpp"
#include "TcpConnection.hpp"
#include "MySql.hpp"
#include <memory>

class UserLoginSection
{
public:
    UserLoginSection(TcpConnectionPtr conn, const Packet & p)
    : _conn(conn)
    , _packet(p)
    , _mysql(std::make_shared<MySql>())
    {}

    //业务逻辑的处理
    void process1();
    string generateSecureSalt(int length)
    
    void process2();
    void sendAuthResponse(bool success);

private:
    void getSetting(string & s, const char * passwd);

private:
    TcpConnectionPtr _conn;
    Packet _packet;
    shared_ptr<MySql> _mysql;
};

// class UserLoginSection2
// {
// public:
//     UserLoginSection2(TcpConnectionPtr conn, const Packet & p)
//     : _conn(conn)
//     , _packet(p)
//     , _mysql(std::make_shared<MySql>())
//     {}

    


// private:
//     TcpConnectionPtr _conn;
//     Packet _packet;
//     shared_ptr<MySql> _mysql; // MySQL数据库操作对象
// };

#endif //__BUSINESSSERVICE_HPP__

