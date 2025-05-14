#ifndef __SOCLET_HPP__
#define __SOCLET_HPP__


//#include <>
class Socket
{
public:
    Socket();
    explicit
    Socket(int _fd);

    ~Socket();

    int fd(){
        return _fd;
    }

    void shutdownWrite();

private:
    int _fd;

};

#endif
