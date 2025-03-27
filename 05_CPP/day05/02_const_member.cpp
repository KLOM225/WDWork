#include <iostream>
using std::cout;
using std::endl;

class Point{
public:
    Point(int x, int y)
    :_x(x)
     ,__y(y)
    {

    }

private:
    const int _x;
    const int _y;
    const int _z = 0;
};

void test(){
    cout << "hello" << endl;
}

int main(){

    test();
    
    return 0;
}

