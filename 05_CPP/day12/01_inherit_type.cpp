#include <my_header.hpp>

class Base{
public:
    int getA()const{
        return _a;
    }

    int _c = 30;

protected:
    int _b = 20;
private:
    int _a = 10;
};

class Derived
:public Base 
{
public:
    void func(){
        // _a是基类私有成员
        // 所以public继承无法获取_a
        //cout << _a << endl;
        cout << _b << endl;
        cout << _c << endl;
        
    }
};

void test(){
    Derived d;
    // d._a;
    // d._b;
    d._c;
    d.getA();
}

int main(){

    test();
    
    return 0;
}

