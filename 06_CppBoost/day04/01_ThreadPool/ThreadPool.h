/**
 * 
 */


#ifndef _THREADPOOL_H
#define _THREADPOOL_H

#include "Task.h"
#include "TaskQueue.h"
#include <thread>

using std::thread;

class ThreadPool {
public: 
    
ThreadPool(size_t threadNum, size_t capa);
    
~ThreadPool();


// 线程池的启动
void start();
    
// 线程池的停止
void stop();
    

void addTask(Task * ptask);

private: 
    size_t _threadNum;
    vector<thread> _threads;
    size_t _capacity;
    TaskQueue _taskQue;
    bool _isExit;
    
Task * getTask();
    
void doTask();
};

#endif //_THREADPOOL_H
