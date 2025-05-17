#include "EventLoop.hpp"
#include "Acceptor.hpp"
#include "TcpConnection.hpp"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/eventfd.h>



EventLoop::EventLoop(Acceptor & a)
:_epfd(createEpollFd())
,_eventfd(createEventFd())
,_isLooping(false)
,_acceptor(a)
,_eventArr(100)
{
    addEpollReadEvent(_acceptor.fd());
    addEpollReadEvent(_eventfd);
}

EventLoop::~EventLoop(){
    close(_epfd);
    close(_eventfd);
}

void EventLoop::loop(){
    _isLooping = true;
    while(_isLooping){
        waitEpollFd();
    }
}

void EventLoop::runInLoop(Functor && cb){
    _mutex.lock();
    _pendingFunctors.push_back(cb);
    _mutex.unlock();
    
    wakeup();
}

void EventLoop::waitEpollFd(){
    int nready = epoll_wait(_epfd, _eventArr.data(), _eventArr.size(), -1);
    if(nready == -1 && errno == EINTR){
        return;
    }else if (nready == -1){
        perror("epoll_wait");
        return;
    }else if (nready == 0){
        printf("epoll timeout.\n");
    }else{
        for(int i = 0; i < nready; ++i){
            int fd = _eventArr[i].data.fd;
            if(fd == _acceptor.fd()){
                handleNewConnection();
            }else if(fd == _eventfd){
                handleRead();
                doPendingFunctors();
            }else{
                handleMessage(fd);
            }
        }
    }
}

void EventLoop::handleNewConnection(){
    int connfd = _acceptor.accept();
    addEpollReadEvent(connfd);
    TcpConnectionPtr sp(new TcpConnection(connfd));
    _conns.insert(std::make_pair(connfd, sp));
    sp->setAllCallbacks(_onConnection, _onMessage, _onClose);
    sp->handleConnectionCallback();
}

void EventLoop::handleMessage(int fd){
    auto iter = _conns.find(fd);
    if(iter != _conns.end()){
        bool isClosed = iter->second->isClosed();
        if(isClosed){
           iter->second->handleCloseCallback();
           delEpollReadEvent(fd);
           _conns.erase(fd);
        }else{
            iter->second->handleMessageCallback();
        }
    }
}

void EventLoop::doPendingFunctors()
{
    printf("doPendingFunctors()\n");
    vector<Functor> tmp;
    _mutex.lock();
    tmp.swap(_pendingFunctors);//时间复杂度为O(1)
    _mutex.unlock();

    for(auto & f : tmp) {
        f();
    }
}


int EventLoop::createEpollFd(){
    int fd = epoll_create1(0);
    if(fd < 0){
        perror("epoll_create1");
    }
    return  fd;
}

void EventLoop::addEpollReadEvent(int fd){
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = EPOLLIN;
    event.data.fd = fd;
    int ret = epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &event);
    if(ret < 0){
        perror("epoll_ctl");
    }
}

void EventLoop::delEpollReadEvent(int fd)
{
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.data.fd = fd;
    int ret = epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, &event);
    if(ret < 0) {
        perror("epoll_ctl");
    }
}


void EventLoop::handleRead()
{
    uint64_t howmany = 0;
    int ret = read(_eventfd, &howmany, sizeof(howmany));
    if(ret != sizeof(howmany)) {
        perror("read");
    }
}

void EventLoop::wakeup()//用来做通知操作
{
    //只要往内核计数器上加1，就能改变其值，从而达到通知的效果
    uint64_t one = 1;
    int ret = write(_eventfd, &one, sizeof(one));
    if(ret != sizeof(one)) {
        perror("write");
    }
}


int EventLoop::createEventFd()
{
    int fd = eventfd(0, 0);
    if(fd < 0) {
        perror("eventfd");
    }
    return fd;
}

