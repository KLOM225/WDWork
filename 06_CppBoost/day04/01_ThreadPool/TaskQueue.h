/*
 * 创建任务队列
 *
 * */


#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H

#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>

using std::queue;
using std::mutex;
using std::cout;
using std::endl;
using std::vector;
using std::condition_variable;
using std::unique_lock;


class Task;

using ElemType = Task *;

class TaskQueue {
public: 
    
    TaskQueue(size_t capa);
    
    ~TaskQueue();


// 在任务队列添加任务
void push(ElemType ptask);

// 取出任务队列的任务
ElemType pop();
    
// 判断任务队列是否满
// 满返回true, 否则返回false
bool full();
    
// 判断任务队列是否空
// 空返回true, 否则返回false
bool empty();
    
void wakeup();

private: 
    size_t _capacity; // 任务队列的容量
    queue<ElemType> _que; // 存储任务的数据结构
    mutex _mutex;   // 互斥锁
    condition_variable _notFull; // 非满条件变量，对应生产者
    condition_variable _notEmpty; // 非空条件变量，对应消费者
    bool _flag; //_notEmpty条件变量上的线程被全部唤醒后的标志位
};

#endif //_TASKQUEUE_H
