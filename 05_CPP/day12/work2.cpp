#include <my_header.hpp>

/* 定义一个点Point类，数据成员是横纵坐标（float）；
定义一个颜色类Color数据成员只有颜色（char*）；
一个直线类Line，数据成员是两个Point对象，表示起点和终点（即Point两个对象为Line的内嵌对象）；
一个三角形类Triangle，继承自Line和Color，数据成员有三角形的高height（float），三角形理解成以基类Color为颜色，以基类直线为底，以height为高的直角三角形，(即直线和高分别为两条直角边)
请实现相关函数，计算三角形的颜色、周长和面积并给出相关输出
*/ 

class Point {
public:
    Point(int x, int y)
    :_x(x)
    ,_y(y)
    {}

    friend class Line;
private:
    float _x;
    float _y;
};

class Color{
public:
    Color(const char * color)
    :_color(new char[strlen(color) + 1]())
    {
        strcpy(_color, color);
    }

    ~Color(){
        if(_color){
            delete [] _color;       
            _color = nullptr;
        }
    }

    void getcolor(){
        cout << _color << endl;
    }
private:
    char *_color;
};

class Line{
public:
    
private:
    Point _p1;
    Point _p2;
};


void test(){
    cout << "hello" << endl;
}

int main(){

    test();
    
    return 0;
}

