#ifndef __SOCKETIO_HPP__
#define __SOCKETIO_HPP__


class SocketIO
{
public:
	explicit
	SocketIO(int fd);

	int readn(char * buff, int len);
	int readline(char * buff, int maxlen);
	int writen(const char * buff, int len);
	int recvPeek(char * buff, int len) const;

	int readPacket(Packet & packet);
private:
	int _fd;
};

#endif 
