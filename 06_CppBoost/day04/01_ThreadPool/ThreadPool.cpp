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
    if(!_taskQue.empty()){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    _isExit = true;
    _taskQue.wakeup();
    for(auto &it : _threads){
        it.join();
    }
}

void ThreadPool::addTask(Task * ptask) {
    if(ptask){
        _taskQue.push(ptask);
    }    
}

Task * ThreadPool::getTask() {

    return _taskQue.pop();    
}

void ThreadPool::doTask() {
    while(!_isExit){
        Task * ptask = getTask();

        if(ptask){
            ptask->process();
        }
        else{
            cout << "ptask == nullptr" << endl;
        }
    }

}

