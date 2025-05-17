#include "TcpServer.hpp"
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;

void onConnection(TcpConnectionPtr conn){
    cout << conn->toString() << "has connected" << endl;
}

void onMessage(TcpConnectionPtr conn)
{
    cout << "before recive msg" << endl;
    string msg = conn->receive();
    cout << "msg.size():" << msg.size() << endl;
    cout << "msg:" << msg << endl;
    sleep(1);
    conn->send(msg);
}

void onClose(TcpConnectionPtr conn)
{
    cout << conn->toString() << " has closed." << endl;
}

int main(void)
{
    TcpServer server(8000);
    server.setAllCallbacks(onConnection, onMessage, onClose);
    server.start();

	return 0;
}
