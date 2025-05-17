#ifndef __Thread_H__
#define __Thread_H__

#include "Noncopyable.hpp"


#include <pthread.h>

#include <functional>


using ThreadCallback = std::function<void()>;

class Thread : Noncopyable
{
public:
    Thread(ThreadCallback && cb);
    void start();
    void join();

private:
    static void * start_routine(void*);//子线程的入口函数


private:
    pthread_t _pthid;
    bool _isRunning;
    ThreadCallback _cb;//函数对象保存要执行的函数
};




#endif

