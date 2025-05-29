#ifndef __BUSINESSSERVICE_HPP__
#define __BUSINESSSERVICE_HPP__

#include "TLV.hpp"
#include "TcpConnection.hpp"
#include "MySql.hpp"

class UserLoginSection1
{
public:
    UserLoginSection1(TcpConnectionPtr conn, const Packet & p)
    : _conn(conn)
    , _packet(p)
    {}

    //业务逻辑的处理
    void process();
    char *GenRandomString(int length);

private:
    void getSetting(string & s, const char * passwd);

private:
    TcpConnectionPtr _conn;
    Packet _packet;
    MySql _mysql; // MySQL数据库操作对象
};

class UserLoginSection2
{
public:
    UserLoginSection2(TcpConnectionPtr conn, const Packet & p)
    : _conn(conn)
    , _packet(p)
    {}

    //业务逻辑的处理
    void process();


private:
    TcpConnectionPtr _conn;
    Packet _packet;
    MySql _mysql; // MySQL数据库操作对象
};

#endif //__BUSINESSSERVICE_HPP__

