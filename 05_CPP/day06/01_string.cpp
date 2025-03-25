#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


void test(){
    string s1("hello cpp");
    string s2 = s1;
    cout << "s1: " << s1 << endl << "s2: " << s2 << endl;
    for (size_t index = 0; index < s1.size(); index++){
        cout << s1[index];
    }
    cout << endl;
    cout << "==========" << endl;

    for(auto & s : s1){
        cout << s << endl;
    }
}

void test2(){
    string s1 = "the world";
    string::iterator it1 = s1.begin();
    auto it2 = s1.end();
    cout << *it1 << endl;
    cout << *(it2-1) << endl;
}

void test3(){
    string s = " the beatiful world";
    auto it1 = s.begin();
    while (it1 != s.end()){
        cout << *it1;
        it1++;
    }

}


int main(){

    test3();
    
    return 0;
}

