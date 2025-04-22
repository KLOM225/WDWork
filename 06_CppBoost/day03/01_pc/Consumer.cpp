#include "Consumer.h"
#include "TaskQueue.h"

#include <iostream>
#include <thread>

using std::cout;
using std::endl;

Consumer::Consumer(){

}
    
Consumer::~Consumer(){

}


void Consumer::consume(TaskQueue &taskQue){
    int cnt = 20;
    while(cnt--){
        int num = taskQue.pop();
        cout << "<<Consumer consume number = " <<  num << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }   
}


