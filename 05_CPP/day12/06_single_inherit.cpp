#include <my_header.hpp>

// 当派生类对象创建时
// 基类里没有无参构造函数
// 派生类的初始化列表没有显示调用基类构造函数
// 不允许派生类对象创建
class Base{
public:
    // 有参构造
    Base(int a)
        :_a(a)
    {
        cout << "Base()" << endl;
    }

    ~Base(){
        cout << "~Base()" << endl;
    }

private:
    int _a;
};


class Derived
:public Base 
{
public:
    Derived(int a,int b)
        :Base(a)
         ,_b(b)
    {
        cout << "Derived()" << endl;
    }
private:
    int _b;
};
void test(){

    Derived d(1, 2);
    cout << sizeof(Base) << endl;
    cout << sizeof(Derived) << endl;
}

void test1(){

    Derived d(1, 2);
    Derived *p = &d;
    int * pint = (int *) p;
    cout << *pint << endl;
    cout << *(pint + 1) << endl;
    cout << &d << endl;
}

void test3(){
    Derived d(1,2);
}

int main(){

    test1();

    return 0;
}

