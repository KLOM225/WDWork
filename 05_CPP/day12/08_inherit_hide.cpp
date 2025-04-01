#include <my_header.hpp>

//派生类对于基类成员的隐藏


class Base{
protected:
    int _data = 10;

};


class Derived
:public Base
{
public:
    void func(){
        cout << _data << endl;
        //这种写法了解即可
        cout << Base::_data << endl;
    }

private:
    int _data = 20;
};


void test(){
    Derived d;
    d.func();

}

int main(){

    test();
    
    return 0;
}

