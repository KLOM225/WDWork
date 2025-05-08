#ifndef _TASK_H
#define _TASK_H

class Task {
public: 
    Task();
    virtual ~Task();

virtual void process() = 0;

};

#endif //_TASK_H
