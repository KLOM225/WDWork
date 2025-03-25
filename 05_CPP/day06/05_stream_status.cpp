#include <my_header.hpp>

void check_stream_status(){
    cout << "cin.goodbit()= " << cin.good() << endl;
    cout << "cin.badbit()= " << cin.bad() << endl;
    cout << "cin.eofbit()= " << cin.eof() << endl;
    cout << "cin.failbit()= " << cin.fail() << endl;

}

void test(){
    int num;
    while(1){
        cout << "输入数字" << endl;
        cin >> num;
        cout << num << endl;

        if(cin.bad() || cin.eof())
        {
            cout << "当前流结束" <<endl;

        }else if(cin.fail())
        {
            cin.clear();
            cin.ignore(1024, '\n');
            cout << "重新输入" << endl;
        }else{
            cout << "num : " << num << endl;
            check_stream_status();
        }
    }
}
int main(){

    test();

    return 0;
}

