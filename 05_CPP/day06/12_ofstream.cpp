#include <my_header.hpp>

// 接收键盘的数据并输入到文件中
void test(){
    ofstream ofs("test.txt");
    
    string str;
    while(cin >> str){
        ofs << str << endl; 
        cout << str << endl;
    }
    ofs.flush();
    ofs.close();

}

void test2(){
    ofstream ofs2("test.txt", std::ios::app);
    ofs2 << "hello" << endl;
    ofs2.flush();
    ofs2.close();

}

int main(){

    test2();
    
    return 0;
}

