#include <my_header.hpp>
#include <functional>

using std::bind;

void func(int x1, int x2, int x3, int &x4, int x5)
{
    cout << "x1 = " << x1 << endl
         << "x2 = " << x2 << endl
         << "x3 = " << x3 << endl
         << "x4 = " << x4 << endl
         << "x5 = " << x5 << endl;
}

void test(){

    //占位符整体代表的是函数的形参；
    //占位符中的数字代表是函数的实参;
    //实参的传递个数要大于等于占位符中数字的最大值;
    //bind的默认传递方式是值传递;
    //如果要使用引用传递，可以使用引用的包装器，std::cref/std::ref
    // ref -- T & x;  cref -- const T & x;

    int num = 100;
    using namespace std::placeholders;
    auto f = bind(func, 10, _1, _2, std::ref(num), num);
    num = 111;
    f(1, 20, 300, 4000, 5000);

}

int main(){

    test();
    
    return 0;
}

