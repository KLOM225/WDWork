#include <my_header.hpp>

//菱形继承解决方案
class A{
public:
    void print(){
        cout << "A::print" << endl;
    }
private:
    double _a = 10;
};

class B
// 使用虚继承
:virtual public A
{
private:
    double _b = 20;
    
};

class C
:virtual public A
{
private:
    double _b = 30;
};

class D
:public B,
public C
{
    public:
    private:
        double _d = 40;
};

void test(){
    D d;
    // 菱形继承导致有多个A
    d.print();
}

int main(){

    test();
    
    return 0;
}

