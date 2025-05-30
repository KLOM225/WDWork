#ifndef __Noncopyable_HPP__
#define __Noncopyable_HPP__


class Noncopyable
{
public:
    Noncopyable(){}
    ~Noncopyable(){}

    //禁止复制
    Noncopyable(const Noncopyable &) = delete;
    Noncopyable & operator=(const Noncopyable &) = delete;

};


#endif // __Noncopyable_HPP__

