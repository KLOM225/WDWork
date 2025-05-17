#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__

#include "Noncopyable.hpp"
#include "Socket.hpp"
#include "InetAddress.hpp"
#include "SocketIO.hpp"

#include <memory>
#include <string>
#include <functional>
using std::string;
using std::shared_ptr;

class EventLoop;


class TcpConnection;
using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectionCallback = std::function<void(TcpConnectionPtr)>;

class TcpConnection
:Noncopyable
,public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(int fd);
    ~TcpConnection();

    string receive();
    void send(const string &msg);
    void sendInLoop(const string & msg);

    string toString() const;
    void shutdown();

    void setAllCallbacks(const TcpConnectionCallback & cb1,
                         const TcpConnectionCallback & cb2,
                         const TcpConnectionCallback & cb3)
    {
        _onConnection = cb1;
        _onMessage = cb2;
        _onClose = cb3;
    }

    void handleConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();
    bool isClosed() const;

private:
    InetAddress getLocalAddr(int fd);
    InetAddress getPeerAddr(int fd);
private:
    Socket _sock;
    SocketIO _socketIo;
    InetAddress _localAddr;
    InetAddress _peerAddr;
    bool _isShutdownWrite;
    EventLoop * _ploop;

    TcpConnectionCallback _onConnection;
    TcpConnectionCallback _onMessage;
    TcpConnectionCallback _onClose;
};



#endif
