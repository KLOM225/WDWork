#include "Thread.hpp"

#include <cstdio>
#include <cstring>

namespace wd{

Thread::Thread()
    :_pthid(0)
    ,_isRunning(false){}

void Thread::start(){
    
    int ret = pthread_create(&_pthid, nullptr, start_routine, nullptr);
    if(ret !=0) {
        fprintf(stderr, "pthread_create: %s\n", strerror(ret));
        return;
    }

    _isRunning = true;
}

void Thread::join(){

}


}
int main(){

    
    return 0;
}

