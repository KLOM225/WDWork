#include <my_header.hpp>

//派生类对于基类成员函数的隐藏


class Base{
public:
    void print(){
        cout << "Base::print" << endl;
    }

private:
    int _data = 10;

};


class Derived
:public Base
{
public:
  void print(int value){
        cout << "Derived::print  " << value << endl;
  }
private:
    int _data = 20;
};


void test(){
    Derived d;

    // d.print();
    d.print(1);
}

int main(){

    test();
    
    return 0;
}

