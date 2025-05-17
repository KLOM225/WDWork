#include "TcpConnection.hpp"
#include "TcpServer.hpp"
#include "Threadpool.hpp"
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;

Threadpool threadpool(4, 10);

class Mytask
{
public:
    Mytask(const string & msg, TcpConnectionPtr conn)
    : _msg(msg)
    , _conn(conn)
    {}

    void process()
    {
        cout << "Mytask is running" << endl;
        string response = _msg;
        

        _conn->sendInLoop(response);
    }

private:
    string _msg;
    TcpConnectionPtr _conn;
};

void onConnection(TcpConnectionPtr conn){
    cout << conn->toString() << "has connected" << endl;
}

void onMessage(TcpConnectionPtr conn)
{
    cout << "before recive msg" << endl;
    string msg = conn->receive();
    cout << "msg.size():" << msg.size() << endl;
    cout << "msg:" << msg << endl;
    

    Mytask mytask(msg, conn);
    threadpool.addTask(std::bind(&Mytask::process, mytask));
}

void onClose(TcpConnectionPtr conn)
{
    cout << conn->toString() << " has closed." << endl;
}

int main(void)
{
    threadpool.start();

    TcpServer server(8000);
    server.setAllCallbacks(onConnection, onMessage, onClose);
    server.start();

	return 0;
}
