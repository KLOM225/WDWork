#ifndef __CONSUMERTHREAD_H__
#define __CONSUMERTHREAD_H__
#include "Thread.hpp"
#include "TaskQueue.hpp"

#include <unistd.h>

#include <iostream>
using std::cout;
using std::endl;


class ConsumerThread: public Thread 
{
public:
    ConsumerThread(TaskQueue & que)
    :_que(que)
    {}
    
private:
    void run() override{
        int cnt = 20;
        while(cnt--){
            int tmp = _que.pop();
            cout << "consume a number : " << tmp << endl;
        }
    }

private: 
    TaskQueue & _que;
};

#endif //__CONSUMERTHREAD_H__
