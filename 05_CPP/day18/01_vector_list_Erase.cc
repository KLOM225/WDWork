#include <my_header.hpp>
#include <list>

//要求:将vector中值为4的元素删除

void test(){
    vector<int> vec{1,2,23,4,4,4,5,4,5,6,78,4,4,7};
    auto it = vec.begin();
    for(; it != vec.end();){
        if(*it == 4){
            vec.erase(it);
        }else{
            ++it;
        }
    }
    for(auto &it1 : vec){
        cout << it1 << " ";
    }
    cout << endl;
}
void test1(){
    list<int> lst{1,2,23,4,4,4,5,4,5,6,78,4,4,7};
    auto it = lst.begin();
    for(; it != lst.end();){
        if(*it == 4){
            // vec.erase(it);
            // list的删除需要返回值，不然迭代器会丢失
            it = lst.erase(it);
        }else{
            ++it;
        }
    }
    for(auto &it1 : lst){
        cout << it1 << " ";
    }
    cout << endl;
}

int main(){

    /* test(); */
    test1();
    return 0;
}

