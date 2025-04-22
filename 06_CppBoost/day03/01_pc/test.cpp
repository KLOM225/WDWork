#include "TaskQueue.h"
#include "Consumer.h"
#include "Producer.h"

#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

void test(){
    TaskQueue taskQue(10);
    Producer proObj;
    Consumer conObj;

    thread pro(&Producer::produce, &proObj, std::ref(taskQue));
    thread con(&Consumer::consume, &conObj, std::ref(taskQue));

    pro.join();
    con.join();
}

int main(){

    test();
    
    return 0;
}

