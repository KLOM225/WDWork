#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threadNum, size_t capa) 
:_threadNum(threadNum)
,_threads()
,_capacity(capa)
,_taskQue(_capacity)
,_isExit(false)
{}

ThreadPool::~ThreadPool() {}

//线程池的启动
void ThreadPool::start() {
    for(size_t i = 0; i < _threadNum; i++){
        _threads.push_back(thread(&ThreadPool::doTask, this));
    }
}

//线程池的停止
void ThreadPool::stop() {
    
}

void ThreadPool::addTask(Task * ptask) {
    return;
}

Task * ThreadPool::getTask() {
    return null;
}

void ThreadPool::doTask() {
    return;
}

