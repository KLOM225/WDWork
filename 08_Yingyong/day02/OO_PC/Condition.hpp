#ifndef _CONDITION_H
#define _CONDITION_H

#include <pthread.h>


namespace wd{

class MutexLock;
class Condition {
public:

    Condition(MutexLock & m);
    ~Condition();

    void wait();

    void notify();

    void notifyAll();


private: 
    pthread_cond_t _cond;
    MutexLock& _mutex;
};

}

#endif //_CONDITION_H
