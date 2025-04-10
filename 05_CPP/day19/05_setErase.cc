#include <my_header.hpp>
#include <set>
#include <utility>

//set的Erase

template <typename Container>
void display(const Container &con){
    for(auto &elme : con){
        cout << elme << " ";
    }
    cout << endl;
}

void test0(){
    
    set<int> num = {1, 3, 5, 9, 7, 8, 10, 10, 9};
    display(num);
    
    //去除连续的奇数
    for(auto it = num.begin(); it != num.end(); ++it){
        // if(*it & 1)
        if(*it % 2 == 1){
            it = num.erase(it);
        }
    }
    display(num);
}

void test()
{
    set<int> number = {1, 3, 5, 9, 7, 8, 10, 10, 9};
    display(number);

    //去除连续的奇数
    for(auto it = number.begin(); it != number.end(); )
    {
        if(*it % 2 == 1)
        {
            it = number.erase(it);
            /* number.erase(it++);//ok */
        }
        else
        {
            ++it;
        }
    }
    display(number);
}


int main(){

    test();
    
    return 0;
}

