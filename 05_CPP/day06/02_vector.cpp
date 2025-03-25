#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

void test(){
    vector <int> num;
    cout << num.size() << endl;

    vector <int> num2(10);
    cout << num2.size() << endl;
    //cout << num2[0] << endl;
    
    vector <int> num3(10,20);
    cout << num3.size() << endl;
    //cout << num3[0] << endl;

    vector<int>num4{1, 2, 3, 4, 5};

    //vector<int>numbers5(num4.begin(), num4.end() -1);
    //cout << num5.size() << endl;
    //cout  << "num[3]" << num5[3] << endl;
    //cout << "num[2]" << num5[2] << endl;
    

}

int main(){

    test();
    
    return 0;
}

