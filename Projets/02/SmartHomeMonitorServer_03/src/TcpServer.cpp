#include "TcpConnection.hpp"
#include "TcpServer.hpp"
#include "Threadpool.hpp"

#include "Configuration.hpp"
#include "SmartHomeMonitorServer.hpp"

#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

int main(void)
{
    Configuration *pconf = Configuration::getInstance();
    SmartHomeMonitorServer server(
        atoi(pconf->getConfigMap()["thread_num"].c_str()),
        atoi(pconf->getConfigMap()["task_num"].c_str()),
        atoi(pconf->getConfigMap()["port"].c_str()));

    server.start();

    return 0;
}
