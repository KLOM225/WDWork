#include "ProducerThread.hpp"
#include "ConsumerThread.hpp"
#include "TaskQueue.hpp"

#include <iostream>
#include <memory>


using std::cout;
using std::endl;
using std::unique_ptr;

int main(){
   
    TaskQueue taskque(10);
    unique_ptr<Thread> producer(new ProducerThread(taskque));
    unique_ptr<Thread> consumer(new ConsumerThread(taskque));

    producer->start();
    consumer->start();

    producer->join();
    consumer->join();

    return 0;
}

