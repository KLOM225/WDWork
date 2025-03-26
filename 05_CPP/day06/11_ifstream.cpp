#include <my_header.hpp>

void test(){
    ifstream ifs("log.txt");
    cout << ifs.good() << endl;

    string line;
    while(getline(ifs, line)){
        cout << line << endl;
    }
    ifs.close();

}

int main(){

    test();
    
    return 0;
}

