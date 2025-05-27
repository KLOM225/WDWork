#include "TcpConnection.hpp"
#include "TcpServer.hpp"
#include "Threadpool.hpp"
#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>
using std::cout;
using std::endl;

class Mytask
{
public:
    Mytask(const string & msg, wd::TcpConnectionPtr conn)
    : _msg(msg)
    , _conn(conn)
    {}

    //process函数在线程池中的某一个子线程来执行的
    //即任务在计算线程中执行
    void process()
    {
        cout << "Mytask is running" << endl;
        //decode
        //compute
        //encode
        string response = _msg;
        //发送消息是在计算线程中进行的
        //
        //从功能的角度上来说，是可以这样做的
        //
        //当从设计的角度上来说，不行，没有做到职责分离
        //考虑程序执行时的局部性原理，也不应该在这里去执行消息的发送
        //
        //如果要达到IO线程发送消息的目标，就应该将该函数的执行延迟到
        //IO线程的事件循环中进行, 即需要知道EventLoop对象的存在，而
        //TcpConnection对象可以达到这个目标
        //_conn->send(response);
        _conn->sendInLoop(response);
    }

private:
    string _msg;
    wd::TcpConnectionPtr _conn;
};



class EchoServer
{
public:
    EchoServer(int num, int quesize, unsigned short port, const string & ip = "0.0.0.0")
    : _threadpool(num, quesize)
    , _server(port, ip)
    {
        //命名空间的使用是限定在构造函数中了,减小其使用范围
        using namespace std::placeholders;
        _server.setAllCallbacks(
            std::bind(&EchoServer::onConnection, this, _1),
            std::bind(&EchoServer::onMessage, this, _1),
            std::bind(&EchoServer::onClose, this, _1));
    }

    void start()
    {
        _threadpool.start();
        _server.start();
    }


    void onConnection(wd::TcpConnectionPtr conn)
    {
        cout << conn->toString() << " has connected" << endl;
    }
     
    //这是消息到达时候的处理方式
    void onMessage(wd::TcpConnectionPtr conn)
    {
        cout << "EchoServer::onMessage is running" << endl;
        //获取消息
        string msg = conn->receive();
        cout << "msg.size():" << msg.size() << endl;
        cout << "msg:" << msg << endl;

        //sleep(1);//模拟任务的执行时间
        //将消息打包成一个任务，交给线程池进行处理
        //IO线程 -> 计算线程
        Mytask mytask(msg, conn);
        _threadpool.addTask(std::bind(&Mytask::process, mytask));
    }

    void onClose(wd::TcpConnectionPtr conn)
    {
        cout << conn->toString() << " has closed." << endl;
    }


private:
    wd::Threadpool _threadpool;
    wd::TcpServer _server;
};

int main(void)
{
    EchoServer server(4, 10, 8000);
    server.start();

	return 0;
}
