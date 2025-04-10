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
    list<int> num {1,2,4,4,4,5,6,7,8,7,7};
    list<int> other = { 4, 66, 77, 66};
    display(num);
    display(other);

    cout << endl;
    auto it = num.begin();
    int i = 1;
    while(i--){
        ++it;
    }
    cout << "*it = " << *it << endl;
    num.splice(it, other);
    display(num);
    display(other);
    cout << "*it = " << *it << endl;

    cout << endl;
    list<int> other2{ 111, 333, 444, 888, 777 };
    auto cit = other2.end();    
    --cit;
    cout << "*cit = " << *cit << endl;
    num.splice(it, other2, cit);
    display(num);
    display(other2);

    cout << endl;
    cit = other2.begin();    
    cit++;
    cout << "*cit = " << *cit << endl;
    auto cit2 = other2.end();    
    --cit2;
    cout << "*cit2 = " << *cit2 << endl;
    num.splice(it, other2, cit, cit2);
    display(num);
    display(other2);

    cout << endl << "在同一个链表中进行splice操作" << endl;
    display(num);
    it = num.begin();
    ++it;
    cout << "*it = " << *it << endl;
    auto it2 = num.end();
    --it2;
    cout << "*it2 = " << *it2 << endl;
    num.splice(it, num, it2);
    display(num);
    
}   

int main(){

    test();
    
    return 0;
}

