#include <my_header.hpp>
//复制控制机制
//派生类对象不显示定义复制控制函数

void test(){
    cout << "hello" << endl;
}

int main(){

    test();
    
    return 0;
}

