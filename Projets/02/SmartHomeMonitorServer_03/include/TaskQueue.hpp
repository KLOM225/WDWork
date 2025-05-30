#ifndef __TaskQueue_HPP__
#define __TaskQueue_HPP__

#include "MutexLock.hpp"
#include "Condition.hpp"
#include "Task.hpp"

#include <iostream>
#include <queue>


//设置一个元素类型
using ElemType=Task;

class TaskQueue
{
public:
    TaskQueue(size_t sz);

    bool empty() const;
    bool full() const;
    void push(ElemType e);
    ElemType pop();
    
    int size() const {  return _que.size();}

    void wakeup();

private:
    std::queue<ElemType> _que;
    size_t _queSize;//表示的是队列元素的最大个数
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
    bool _flag;

};


#endif

