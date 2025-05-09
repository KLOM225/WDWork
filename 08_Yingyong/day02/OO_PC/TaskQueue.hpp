#ifndef __TASKQUEUE_HPP__
#define __TASKQUEUE_HPP__

#include "MutexLock.hpp"
#include "Condition.hpp"

#include <iostream>
#include <queue>
#include <cstdio>


class TaskQueue {
public: 

    TaskQueue(size_t size);

    void push(int);

    int pop();

    bool empty() const;

    bool full() const;

private: 
    std::queue<int> _que;
    int _queSize;
    wd::MutexLock _mutex;
    wd::Condition _notFull;
    wd::Condition _notEmpty;
};

#endif //__TASKQUEUE_HPP__
