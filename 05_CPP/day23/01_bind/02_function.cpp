#include <my_header.hpp>
#include <functional>


int add (int x, int y){
    cout << "int add (int, int)" << endl;
    return x + y;
}

int multiplay(int x, int y, int z){
    cout << "multiplay(int, int, int)" << endl;
    return x * y * z;
}

class Example{
public:
    int add (int x, int y){
        cout << "int Example::add (int, int)" << endl;
        return x + y;
    }
};


void test(){
    //add的函数形态（类型、标签）:函数的返回类型 + 函数的参数列表（参数的
    //个数、顺序、类型）
    //add的类型：int(int, int)
    //bind改变了函数的形态
    //f的类型：int()
    /* auto f = bind(&add, 1, 3); */
    //function可以存放函数的类型，将function称为函数的容器
    



}

int main(){

    test();
    
    return 0;
}

