#include <my_header.hpp>
#include <functional>


vector<function<void(const string &)>> vec;

void test(){
    int num = 100;
    string name("wangdao");
    function<void(const string&)> f =
        [&num, &name](const string &value)->void{
            cout << "num = " << num << endl;
            cout << "name = " << name << endl;
            cout << "value = " << value << endl;
        };
    f("cccc");

    /* vec.push_back([&num, &name](const string &value){ */
    vec.push_back([num, name](const string &value){
                    cout << "num = " << num << endl;
                    cout << "name = " << name << endl;
                    cout << "value = " << value << endl;
                  });
    
}


void test2(){
    for(auto &f : vec){
        f("wuhan");
    }

}
int main(){

    test();
    test2();
    return 0;
}

