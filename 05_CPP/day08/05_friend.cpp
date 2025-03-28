#include <my_header.hpp>
#include <cmath>



class Point{
public:
    Point(int x, int y)
        :_x(x)
         ,_y(y)
    {
        cout << "Point(int,int)" << endl;
    }

friend class Line;
private:
    int _x;
    int _y;
};


class Line{
public:
    float distance(const Point &pt1, const Point &pt2);
};

float Line::distance(const Point &pt1, const Point &pt2){
        int x1 = pt1._x;
        int y1 = pt1._y;

        int x2 = pt2._x;
        int y2 = pt2._y;

        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }


void test(){
    Point pt1(3,5), pt2(5,7);
    Line line;
    float x = line.distance(pt1, pt2);

    cout << x << endl;
}

int main(){

    test();

    return 0;
}

