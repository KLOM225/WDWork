#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include <pthread.h>

class Thread {
public: 

    Thread();

    void start();

    void join();
private: 
    pthread_t _pthid;
    bool _isRunning;

    static void* start_routine(void*);

    virtual void run() = 0;
};

#endif // __THREAD_HPP__
