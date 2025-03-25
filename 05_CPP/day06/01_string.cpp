#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;


void test(){
    string s1("hello cpp");
    string s2 = s1;
    cout << "s1" << s1 << ", s2" << s2 << endl;
}


int main(){

    test();
    
    return 0;
}

