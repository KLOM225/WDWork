#ifndef __PRODUCERTHREAD_HPP__
#define __PRODUCERTHREAD_HPP__

#include "Thread.hpp"
#include "TaskQueue.hpp"

#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

class ProducerThread: public Thread {
public: 

    ProducerThread(TaskQueue & que)
    :_que(que)
    {};

private:
    void run(){
        srand(time(nullptr));
        int cnt = 20;
        while(cnt-- > 0) {
            int num = rand() % 100;
            _que.push(num);
            cout << "producer a num :" << num << endl;
        }
    }

private: 
    TaskQueue & _que;
};


#endif //__PRODUCERTHREAD_HPP__
