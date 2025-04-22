#ifndef __TQSKQUEUE_H__
#define __TQSKQUEUE_H__

#include <queue>
#include <mutex>
#include <condition_variable>

using std::mutex;
using std::queue;
using std::condition_variable;
using std::unique_lock;

class TaskQueue{
public:
    TaskQueue(size_t capa);
    ~TaskQueue();

    void push(const int & value);
    int pop();

    bool full();
    bool empty();

private:
    size_t _capacity;
    queue<int> _que;
    mutex _mutex;
    condition_variable _notFull;
    condition_variable _notEmpty;
};


#endif
