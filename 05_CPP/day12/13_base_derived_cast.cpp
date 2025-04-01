#include <my_header.hpp>
//基类和派生类对象之间的相互转换

class Base{
private:
    int _base = 10;
};

class Derived
:
public Base
{
private:
    int _derived = 20;
};



void test(){
    Base base;
    Derived der;

    // der = base; 
    base = der;
    
    Base * pbase = &der;
    // Derived * pder = &base;
    
    Base & ref_base = der;    
    // Derived & ref_der = base;

}

int main(){

    test();
    
    return 0;
}

