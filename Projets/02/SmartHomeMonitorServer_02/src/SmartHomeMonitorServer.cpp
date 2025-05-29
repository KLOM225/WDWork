#include "SmartHomeMonitorServer.hpp"
#include "BusinessService.hpp"
#include "TLV.hpp"
#include "Mylogger.hpp"

#include <iostream>

using std::cout;
using std::endl;

SmartHomeMonitorServer::SmartHomeMonitorServer(int num, int quesize, unsigned short port, const string &ip)
    : _threadpool(num, quesize), _server(port, ip)
{
    using namespace std::placeholders;
    _server.setAllCallbacks(
        std::bind(&SmartHomeMonitorServer::onConnection, this, _1),
        std::bind(&SmartHomeMonitorServer::onMessage, this, _1),
        std::bind(&SmartHomeMonitorServer::onClose, this, _1));
}

void SmartHomeMonitorServer::start()
{
    _threadpool.start();
    _server.start();
}

void SmartHomeMonitorServer::stop()
{
    _server.stop();
    _threadpool.stop();
}

void SmartHomeMonitorServer::onConnection(TcpConnectionPtr conn)
{
    LogInfo("tcp %s has connected.\n", conn->toString().c_str());
}

void SmartHomeMonitorServer::onMessage(TcpConnectionPtr conn)
{

    cout << "onMessage..." << endl;
    Packet packet; // 解析TLV格式之后的消息放在packet中
    int ret = conn->readPacket(packet);
    cout << "read:" << ret << "bytes.\n";
    cout << "packet.type: " << packet.type << endl
         << "packet.length:" << packet.length << endl
         << "pakcet.msg:" << packet.msg << endl;

    // handleTask((wd::TaskType)packet.type);
    switch (packet.type)
    {
    case TASK_TYPE_LOGIN_SECTION1:
    {
        UserLoginSection1 userLogin1(conn, packet);
        _threadpool.addTask(std::bind(&UserLoginSection1::process, userLogin1));
    }
    break;
    case TASK_TYPE_LOGIN_SECTION2:
    {
        UserLoginSection2 userLogin2(conn, packet);
        _threadpool.addTask(std::bind(&UserLoginSection2::process, userLogin2));
    }
    break;
    }
}

void SmartHomeMonitorServer::onClose(TcpConnectionPtr conn)
{
    LogInfo("tcp %s has closed.\n", conn->toString().c_str());
}