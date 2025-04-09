#include <my_header.hpp>


template <typename Container>
void display(const Container &con){
    for(auto &elem : con){
        cout << elem << " ";
    }
    cout << endl;
}

void printCapacity(const vector<int> &vec){
    cout << "size() = " << vec.size() << endl;
    cout << "capacity() = " << vec. capacity() << endl;
}

void test(){
    cout << "sizeof(vector<int>) = " << sizeof(vector<int>) << endl;
    cout << "sizeof(vector<long>) = " << sizeof(vector<long>) << endl;
    vector<int> num = {1,2, 3,4,5,6,7,8,9};
    display(num);
    printCapacity(num);

    cout << endl <<"在vector的尾部进行插入与删除" << endl;
    num.push_back(10);
    num.push_back(20);
    display(num);
    printCapacity(num);
    num.pop_back();
    display(num);
    printCapacity(num);

    cout << endl << "在vector的任意位置进行插入" << endl;
    vector<int>::iterator it;
    it = num.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    num.insert(it, 100);
    display(num);
    printCapacity(num);
    cout << "*it = " << *it << endl;
    
    cout << endl;
    it = num.begin();
    ++it;
    ++it;
    cout << "*it = " << *it << endl;
    num.insert(it, 6, 999);
    display(num);
    printCapacity(num);
    cout << "*it = " << *it << endl;

    
    cout << endl << "vector清空元素" << endl;
    num.clear();//清空元素
    num.shrink_to_fit();//回收多余的空间
    cout << "size() = " << num.size() << endl;
    cout << "capacity() = " << num.capacity() << endl;


}



int main(){

    test();
    
    return 0;
}

