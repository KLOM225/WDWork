#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "Socket.hpp"
#include "InetAddress.hpp"

class Acceptor
{
public:
    Acceptor(unsigned short port, const string &ip = "0.0.0.0");
    
    void ready();
    
    int fd() const{
        return  _listensock.fd();
    }

    int accept();
private:
    void setReuseAddr(bool on);
	void setReusePort(bool on);
	void bind();
	void listen();

private:
    InetAddress _addr;
    Socket _listensock;
};

#endif
