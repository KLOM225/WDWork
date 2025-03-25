#include <my_header.hpp>

void check_stream_status(){
    cout << "cin.goodbit()= " << cin.good() << endl;
    cout << "cin.badbit()= " << cin.bad() << endl;
    cout << "cin.eofbit()= " << cin.eof() << endl;
    cout << "cin.failbit()= " << cin.fail() << endl;

}

void test(){
    check_stream_status();
    int num;
    cin >> num;
    cout << num << endl;
    check_stream_status();
    cout << "第二次输入数字，输入错误" << endl;
    cin >> num;
    cout << num << endl;
    check_stream_status();
    cout << "=========" << endl;

    string str;
    cin >> str;
    cout << str << endl;
    check_stream_status();

    cout << "+++++++++" << endl;
    cout << "str: " << str << endl;
    if(cin.fail()){
        cin.clear();
        cin.ignore(1024, '\n');
        cin >> str;
    }
    cout << "str: " << str << endl;
    check_stream_status();
}

int main(){

    test();
    
    return 0;
}

