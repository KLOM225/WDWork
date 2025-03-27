#include <iostream>
using std::cout;
using std::endl;

class Point{
public:
    Point(int x, int y)
        :_x(x), _y(y){

        }
private:
    int _x;
    int _y;
};

Point pt(1, 2);

Point func(){
    return pt;
}

void test(){
    int a = 10;
    cout << &a << endl;
    

    cout << &"hello,Cpp" << endl;
    int & ref2 = a;
    const int &ref = 10;
    const Point & ref4 = func();
}

int main(){

    test();
    
    return 0;
}

