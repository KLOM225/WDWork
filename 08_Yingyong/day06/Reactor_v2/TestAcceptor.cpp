#include "Acceptor.hpp"
#include "TcpConnection.hpp"
#include "EventLoop.hpp"

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

void onConnection(TcpConnectionPtr conn)
{
    cout << conn->toString() << " has connected" << endl;
}

void onMessage(TcpConnectionPtr conn)
{
    cout << "before recive msg" << endl;
    string msg = conn->receive();
    cout << "msg.size():" << msg.size() << endl;
    cout << "msg:" << msg << endl;
    conn->send(msg);
}

void onClose(TcpConnectionPtr conn)
{
    cout << conn->toString() << " has closed." << endl;
}

int main(void)
{
	Acceptor acceptor(8000);
	acceptor.ready();
    EventLoop loop(acceptor);
    loop.setAllCallbacks(onConnection, onMessage, onClose);
    cout << "connecting"<< endl;
    loop.loop();
	return 0;
}

