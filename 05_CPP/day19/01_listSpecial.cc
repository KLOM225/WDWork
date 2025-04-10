#include <my_header.hpp>
#include <list>


template <typename Container>
void display(const Container &con){
    for (auto &elme : con){
        cout << elme << " ";
    }
    cout << endl;
}



void test(){
    list<int> num {1,2,3,4,4,4,5,5,5,6,7,8,9,7,7,7};
    display(num);


    cout << endl << "list的unique函数" << endl;
    num.unique();
    display(num);

    cout << endl << "list的sort函数" << endl;
    num.sort();
    display(num);

    cout << endl << "list的reverse函数" << endl;
    num.reverse();
    display(num);
    
    cout << endl << "list的unique函数" << endl;
    num.unique();
    display(num);

    
    cout << endl << "list的merge函数" << endl;
    num.sort();
    display(num);
    list<int> other = { 4, 66, 77, 7, 56, 66};
    other.sort();
    display(other);
    num.merge(other);
    display(num);
    display(other);


}   

int main(){

    test();
    
    return 0;
}

