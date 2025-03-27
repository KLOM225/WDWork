#include <iostream>
using std::cout;
using std::endl;

class Point{
public:
    Point(int x, int y)
    :_x(x), _y(y)
    {
        cout << "Point(int, int)" << endl;
    }
    //拷贝构造函数
    Point(const Point & rhs)
    :_x(rhs._x), _y(rhs._y)
    {
        cout << "Point(const Point & rhs)" << endl;
    }


private:
    int _x;
    int _y;
};

void test(){
    Point pt(1, 2);
    //当你在写这行代码时候，底层调用的便是拷贝构造函数
    //Point pt2 = pt;
    //如果直接编译运行，可能无法看到拷贝构造函数的调用
    //可以再编译的时候加上 -fno-elide-constructors --std=c++11
    //这个指令是去优化指令，就可以拷贝构造函数的调用了
    Point pt2 = Point(1, 2);
}

int main(){

    test();
    
    return 0;
}

