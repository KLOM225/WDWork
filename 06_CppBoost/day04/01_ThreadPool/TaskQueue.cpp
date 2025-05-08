#include "TaskQueue.h"


// 初始化
TaskQueue::TaskQueue(size_t capa)
    :_capacity(capa)
    ,_que()
    ,_mutex()
    ,_notFull()
    ,_notEmpty()
     ,_flag(true)
{}

TaskQueue::~TaskQueue() {}


void TaskQueue::push(ElemType ptask) {

    // 获取锁
    unique_lock<mutex> u1(_mutex);

    while(full()){
        // 如果容器满了
        // 则在条件队列上等待
        _notFull.wait(u1); 

    }
    // 如果容器不满，将创建线程
    // 并压入容器
    _que.push(ptask);
    // 并唤醒等待列表
    _notEmpty.notify_one();

}

ElemType TaskQueue::pop() {
    // 获取锁
    unique_lock<mutex> u2(_mutex);

    while(empty() && _flag){
        // 如果容器为空，则在条件队列上等待
        _notEmpty.wait(u2);
    }
    if(_flag){
        // 如果不空，则弹出任务
        // 并返回
        auto temp = _que.front();
        _que.pop();
        // 唤醒等待列表，继续产生任务
        _notFull.notify_one();
        return temp;
    }
    else{
        return nullptr;
    }
}

bool TaskQueue::full() {

    return _capacity == _que.size();
}

bool TaskQueue::empty() {

    return 0 == _que.size();
}

void TaskQueue::wakeup() {
    _flag = false;
    _notEmpty.notify_all();
}
