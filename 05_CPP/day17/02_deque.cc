#include <my_header.hpp>
#include <deque>
//deque容器初始化

void test(){
    deque<int> num;
    deque<int> num1(3, 10);
    deque<int> num2{1,2,3,4,5,6,7,8,9};
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};  
    // deque<int> num3(arr, arr + 9);
    // 0 1 2 3 4 5 6 7 8

    cout << "idx" << endl;
    deque<int> num3(arr, arr + 10);
    for(size_t idx = 0; idx < num3.size(); ++idx){
        cout <<  num3[idx] << " ";
    }
    cout << endl;
    
    //未初始化的迭代器
    cout << "iterator " << endl;
    deque<int>::iterator it;
    for(it = num3.begin(); it != num3.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
    

    //初始化的迭代器
    cout << "iterator_init " << endl;
    deque<int>::iterator it1 = num3.begin();
    for(; it1 != num3.end(); ++it1){
        cout << *it1 << " ";
    }
    cout << endl;
    
    //增强for循环
    cout << "auto &it " << endl;
    for(auto &it2 : num3){
        cout << it2 << " ";
    }
    cout << endl;

}

int main(){

    test();
    
    return 0;
}

