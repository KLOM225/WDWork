#ifndef __BUSINESSSERVICE_HPP__
#define __BUSINESSSERVICE_HPP__

#include "TLV.hpp"
#include "TcpConnection.hpp"
#include "MySql.hpp"
#include <memory>

class UserLoginSection1
{
public:
    UserLoginSection1(TcpConnectionPtr conn, const Packet & p)
    : _conn(conn)
    , _packet(p)
    , _mysql()
    {}

    //业务逻辑的处理
    void process();
    char *GenRandomString(int length);

private:
    void getSetting(string & s, const char * passwd);

private:
    TcpConnectionPtr _conn;
    Packet _packet;
    shared_ptr<MySql> _mysql;
};

class UserLoginSection2
{
public:
    UserLoginSection2(TcpConnectionPtr conn, const Packet & p)
    : _conn(conn)
    , _packet(p)
    , _mysql()
    {}

    //业务逻辑的处理
    void process();


private:
    TcpConnectionPtr _conn;
    Packet _packet;
    shared_ptr<MySql> _mysql; // MySQL数据库操作对象
};

#endif //__BUSINESSSERVICE_HPP__

