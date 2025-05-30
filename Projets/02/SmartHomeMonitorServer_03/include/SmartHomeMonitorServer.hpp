#ifndef __SMARTHOMEMONITOR_SERVER_HPP__
#define __SMARTHOMEMONITOR_SERVER_HPP__

#include "TcpServer.hpp"
#include "Threadpool.hpp"
#include "Configuration.hpp"

#include <iostream>

using std::cout;
using std::endl;


class SmartHomeMonitorServer
{
public:
    SmartHomeMonitorServer(int num, int quesize, unsigned short port, const string & ip = "0.0.0.0");

    void start();
    void stop();

    void onConnection(TcpConnectionPtr conn);
     
    //这是消息到达时候的处理方式
    void onMessage(TcpConnectionPtr conn);

    void onClose(TcpConnectionPtr conn);


private:
    Threadpool _threadpool;
    TcpServer _server;
};


#endif // __SMARTHOMEMONITOR_SERVER_HPP__