#include <my_header.hpp>

void test(){
    ifstream ifs;
    ifs.open("log.txt");
    cout << ifs.good() << endl;
    // ifstream ifs("log.txt");

    string word;
    while(ifs >> word){
        cout << word << endl;
    }
    ifs.close();

}

int main(){

    test();
    
    return 0;
}

