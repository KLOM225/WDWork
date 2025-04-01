#include <my_header.hpp>


class Base{
public:
    Base(){
        cout << "Base()" << endl;
    }
};


class Derived
:public Base 
{
public:
    Derived(){
        cout << "Derived()" << endl;
    }
};


void test(){
    Derived d;
}

int main(){

    test();
    
    return 0;
}

