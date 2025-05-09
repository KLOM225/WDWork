#include "TaskQueue.hpp"
#include "MutexLock.hpp"

#include <iostream>

TaskQueue::TaskQueue(size_t size) 
:_queSize(size)
,_mutex()
,_notFull(_mutex)
,_notEmpty(_mutex)
{
    
}

bool TaskQueue::empty()const {
    return _que.size() == 0;
}

bool TaskQueue::full() const{
    return _que.size() == _queSize;
}

void TaskQueue::push(int num) {
    wd::MutexLockGuard autolock(_mutex);
    if(full()){
        _notFull.wait();
    }

    _que.push(num);
    _notEmpty.notify();
}

int TaskQueue::pop() {
    wd::MutexLockGuard autolock(_mutex);
    while(empty()){
        _notEmpty.wait();
    }
    int tmp = _que.front();
    _que.pop();

    _notFull.notify();
    return tmp;
}
