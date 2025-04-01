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
// 保护继承
:protected Base 
{
   // 派生类中 
public:
    void func(){
        // _a是基类私有成员
        // 所以protected继承无法获取_a
        //在类中可以访问处pivate成员外其他
        //cout << _a << endl;
        cout << _b << endl;
        cout << _c << endl;
        
    }
};

void test(){
    Derived d; //派生类对象
    // protected继承导致访问无效
    // d._a;
    // d._b;
    // d._c;
    // d.getA();
    d.func();    
}


int main(){

    test();
    
    return 0;
}

