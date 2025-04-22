#include "TaskQueue.h"


TaskQueue::TaskQueue(size_t capa)
    :_capacity(capa)
    ,_que()
    ,_mutex()
    ,_notFull()
    ,_notEmpty()
    {

    }

TaskQueue::~TaskQueue(){}

// 生产者生产数据
void TaskQueue::push(const int & value){
    // 1.上锁
    /* _mutex.lock(); */
    unique_lock<mutex> u1(_mutex);
    // 2.判满
    if(full()){
    // 2.1 如果是满的，在条件变量上睡眠
    _notFull.wait(u1);
    }
    // 2.2 如果不满，生产数据。存放在任务队列中
    _que.push(value);
    // 并且唤醒消费者消费数据
    _notEmpty.notify_one();
    // 3.释放锁
    /* _mutex.unlock(); */
}


int TaskQueue::pop(){
    // 1.上锁
    unique_lock<mutex> u1(_mutex);
    // 2.判空
    if(empty()){
        // 2.1如果为空，在条件变量上睡眠
        _notEmpty.wait(u1);
    }
    // 2.2如果不空，消费数据，从任务队列中获取数据
    int temp = _que.front();
    _que.pop();
    // 唤醒生产者生产数据
    _notFull.notify_one();
    // 3.解锁
    return temp;
}


bool TaskQueue::full(){
    /* if(_que.size() == _capacity){ */
    /*     return  true; */
    /* }else{ */
    /*     return false; */
    /* } */
    return _capacity == _que.size();
}

bool TaskQueue::empty(){
    return 0 == _que.size();

}

