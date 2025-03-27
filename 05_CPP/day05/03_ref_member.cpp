#include <iostream>
using std::cout;
using std::endl;

class Point{
public:
    Point()
    :_x(x)
    ,_y(y)
    ,_z(_x)
    {
        cout << "Point(int,int)" << endl;
    }

    void print(){
        cout << "_x=" << _x << ",_y=" << _y << ",_z=" << _z << endl; 
    }

private:
    int _x;
    int _y;
    int &_z;
};
void test(){
    cout << "hello" << endl;
}

int main(){

    test();
    
    return 0;
}

