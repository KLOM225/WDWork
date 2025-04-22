#include "Producer.h"
#include "TaskQueue.h"

#include <time.h>
#include <stdlib.h>
#include <thread>

#include <iostream>

using std::cout;
using std::endl;

Producer::Producer() {}
Producer::~Producer() {}

void Producer::produce(TaskQueue &taskQue){
    ::srand(clock());
    
    int cnt = 20;
    while(cnt--){
        int number = ::rand() % 100;
        taskQue.push(number);
        cout << ">>Producer produce number = " << number << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
    


