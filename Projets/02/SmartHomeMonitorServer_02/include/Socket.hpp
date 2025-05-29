#ifndef __SOCKET_HPP__
#define __SOCKET_HPP__

#include "Noncopyable.hpp"


class Socket
: Noncopyable  //继承自Noncopyable类，禁止复制
{
public:
	Socket();
	explicit
	Socket(int fd);

    int fd() const { return _fd;   }

	void shutdownWrite();

	~Socket();

private:
	int _fd;
};


#endif // __SOCKET_HPP__
