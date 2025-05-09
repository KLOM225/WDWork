#include "Thread.hpp"

#include <cstdio>
#include <cstring>

Thread::Thread() 
:_pthid(0)
,_isRunning(false) 
{

}

void Thread::start() {
    int ret = pthread_create(&_pthid, nullptr, &start_routine, this);
    if(ret != 0){
        fprintf(stderr, "pthread_create: %s\n", strerror(ret));
        return;
    }
    _isRunning = true;
    
}

void* Thread::start_routine(void* arg) {
    Thread *pthread = static_cast<Thread*>(arg);

    if(pthread)
        pthread->run();

    return nullptr;
}

void Thread::join() {
    if(_isRunning){
        pthread_join(_pthid, nullptr);
        _isRunning = false;
    }
    
}


