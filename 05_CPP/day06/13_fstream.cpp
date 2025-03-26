#include <my_header.hpp>

void test(){
    fstream fs("test.txt");

    int num;
    if(!fs.good()){
        cout << "fail" << endl;
        return;
    }
    for (size_t i = 0; i < 5; i++) {
        cin >> num;
        fs << num << " ";
    }
    fs.flush();
    
    //两种回到文件开头的方式
    // cout << fs.tellg() << endl;
    
    fs.seekg(0, std::ios::beg);
    
    int num2;
    for (size_t i = 0; i < 5; i++){
        fs >> num2;
        cout << num2 << " ";

    }
    cout << endl;
    fs.close();
}

int main(){

    test();

    return 0;
}

