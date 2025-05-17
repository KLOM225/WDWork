#include "EventLoop.hpp"
#include "Acceptor.hpp"
#include "TcpConnection.hpp"
#include <errno.h>
#include <stdio.h>
#include <string.h>

EventLoop::EventLoop(Acceptor & a)
:_epfd(createEpollFd())
,_acceptor(a)
,_isLooping(false)
,_eventArr(100)
{
    addEpollReadEvent(_acceptor.fd());
}

void EventLoop::loop(){
    _isLooping = true;
    while(_isLooping){
        waitEpollFd();
    }
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

