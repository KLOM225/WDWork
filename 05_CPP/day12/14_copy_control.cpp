#include <my_header.hpp>

class Base{
public:
    Base(const char * base)
    :_pbase(new char[strlen(base) + 1]())
    {
        strcpy(_pbase, base);
        cout << "Base(const char *)" << endl;
    }
    //三原则
    ~Base(){
        if(_pbase){
            delete [] _pbase;
            _pbase = nullptr;
        }
        cout << "~Base()" << endl;
    }

    Base(const Base & rhs)
    :_pbase(new char[strlen(rhs._pbase) + 1]())
    {
        strcpy(_pbase, rhs._pbase);
        cout << "Base(const Base & rhs)" << endl;
    }

    Base & operator=(const Base & rhs){
        if(this != &rhs){
            delete [] _pbase;
            _pbase = new char[strlen(rhs._pbase) + 1]();
            strcpy(_pbase, rhs._pbase);
        }
        return *this;
    }

protected:
    char * _pbase;
};

class Derived
:
public
Base{
public:
    Derived(const char * base)
    :Base(base)
    {
        cout << "Derived(const char *)" << endl;
    }
    //这里面不去写复制控制函数：拷贝构造函数、赋值运算符函数

    void print(){
        cout << _pbase << endl;
    }
};


void test(){
    Derived d("hello");
    //复制控制 
    Derived d1 = d;
    d.print();
    d1.print();
    Derived d2("world");
    d2 = d;
    d.print();
    d2.print();
}

int main()
{
    test();
    return 0;
}
