#include <my_header.hpp>
#include <list>

//题目：编写代码：将一个list中的char *指针元素赋值给一个vector中的string。
//提示：加入list的定义如下，
//list<char*> lst= { "hello", "world", "!" };
//如何将list中的内容赋值给vector<string>


void test(){
    list<const char *> lst{"hello", "world", "!"};
    vector<string> vec(lst.begin(), lst.end());
    for(auto &it : vec){
        cout << it << " ";
    }
    cout << endl;
}

int main(){

    test();
    
    return 0;
}

