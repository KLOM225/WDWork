#include <my_header.hpp>
#include <list>
#include <deque>

//编程题：从一个 list 拷贝元素到两个 deque 中。
//值为偶数的所有元素都拷贝到一个 deque 中，而奇数值元素都拷贝到另一个 deque 中。
//提示：熟悉list容器与deque容器的基本操作，包括初始化、遍历、插入等等
void test(){
    list<int> ls{1,2,3,4,5,6,7,8,9,10};
    deque<int> deqOdd, deqEven;
    auto it = ls.begin();
    while(it != ls.end()){
        if(*it % 2){
            deqOdd.push_back(*it);
            ++it;
        }else{
            deqEven.push_back(*it);
            ++it;
        }
    }
    for(auto it2 = deqOdd.begin(); it2 != deqOdd.end(); ++it2){
        cout << *it2 << " ";
    }
    cout << endl;
    for(auto it3 = deqEven.begin(); it3 != deqEven.end(); ++it3){
        cout << *it3 << " ";
    }
    cout << endl;



}

int main(){

    test();
    
    return 0;
}

