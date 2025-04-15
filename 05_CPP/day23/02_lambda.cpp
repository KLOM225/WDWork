#include <my_header.hpp>
#include <functional>


void test(){
    int num = 10;
    /* auto f = [num](int value)->void{}; */
    function<void(int)> f = [num](int value)->void{
        cout << "value = " << value << endl;
        cout << "num = " << num << endl;
    };

    f(30);
}

int main(){

    test();
    
    return 0;
}

