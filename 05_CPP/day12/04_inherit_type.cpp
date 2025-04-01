#include <my_header.hpp>

// protected 与 private 继承的区别
class GrandPa{
public:
    int _a = 10;
protected:
    int _b = 20;
private:

};

class Parent
:private GrandPa
{

};


class Son
:public Parent
{
public:
    void func(){
        // 由于父类型是private 继承
        // 所以无法访问上面的所有类型
        // 被parent 派生类截断了
        // cout << _a << endl;
        // cout << _b << endl;
    }
};



void test(){
}

int main(){

    test();
    
    return 0;
}

