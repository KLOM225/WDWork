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

    int getx() const{
        return _x;
    }

    int gety() const{
        return _y;
    }
    

private:
    int _x;
    int _y;
};

float distance(const Point &pt1, const Point &pt2){
    int x1 = pt1.getx();
    int y1 = pt1.gety();
    
    int x2 = pt2.getx();
    int y2 = pt2.gety();
    
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

}

void test(){
    Point pt1(3,5), pt2(5,7);
    float x = distance(pt1, pt2);

    cout << x << endl;
}

int main(){

    test();
    
    return 0;
}

