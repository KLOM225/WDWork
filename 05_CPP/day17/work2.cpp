#include <my_header.hpp>
#include <deque>
//编程题：从标准输入读取 string 序列，存入一个 deque 中。
//编写一个循环，用迭代器打印 deque 中的元素。
//提示：熟悉deque的基本函数的使用方式。

void test(){
    deque<string> deq;
    string str;
    while(cin >> str){
        deq.push_back(str);
    }
    cout << "deque" << endl;
    for(auto &it : deq){
        cout << it << endl;
    }
    
}

int main(){

    test();
    
    return 0;
}

