#include <my_header.hpp>

//读取文件指定位置的内容
void test(){
    fstream fs("test.txt");

    if(!fs.good()){
        cout << "fail" << endl;
        return;
    }

    int begindex = 3;
    int endindex = 15;

    fs.seekg(0, std::ios::end);
    int length = fs.tellg();
    if(length < endindex){
        cout << "fs length < readindex" << endl;
        return;
    }
    fs.seekg(begindex);

    char *str = new char[endindex - begindex + 1]();
    fs.read(str, endindex - begindex);
    fs.flush();
    fs.close();
    
    cout << str << endl;
    delete  [] str;
    str = nullptr;
}

int main(){

    test();

    return 0;
}

