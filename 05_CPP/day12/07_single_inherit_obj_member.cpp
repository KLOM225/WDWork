#include <my_header.hpp>

class Base{
public:
    Base(int base)
    :_base(base)
    {
        cout << "Base(int)" << endl;
    }

    ~Base(){
        cout << "~Base()" << endl;
    }

private:
    int _base;
};

class ThirdOb{
public:
    ThirdOb(int num)
    :_num(num)
    {
        cout << "ThirdOb(int)" << endl;
    }
    
    ~ThirdOb(){
        cout << "~ThirdOb()" << endl;
    }

private:
    int _num;
};

class Derived
:public Base 
{
    public:
        Derived(int base, int num,int der)
        :Base(base * 2)
        ,_td(num)
        ,_base(base)
        ,_der(der)
        {

        }
    private:
        ThirdOb _td;
        Base _base;
        int _der;
};



void test(){
    Derived d(1,2,3);
}

int main(){

    test();
    
    return 0;
}

