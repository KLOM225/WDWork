#include "Task.h"
#include "TaskQueue.h"
#include "ThreadPool.h"

#include <ctime>

using std::unique_ptr;

class myTask
:public Task
{
public:
    void process() override
    {   
        ::srand(::clock());
        int number = ::rand() % 100;
        cout << "MyTask number = " << number << endl;
    }
};

void test(){
    
    unique_ptr<Task> ptask(new myTask());
    ThreadPool pool(4, 10);
    myTask mt;
    pool.start();
    int num = 20;
    while(num--){
        pool.addTask(ptask.get());
        cout << "num = " << num << endl;
    }

    pool.stop();
}

int main(){

    test();
    
    return 0;
}

