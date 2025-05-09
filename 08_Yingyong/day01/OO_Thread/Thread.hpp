#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

namespace wd{

class Thread
{
public:
    Thread();
    ~Thread();

    void start();
    void join();

private:
    static void *start_routine(void *);

    virtual void run() = 0;

private:
    pthread_t _pthid;
    bool _isRunning;
};

}//end of namespace wd

#endif

