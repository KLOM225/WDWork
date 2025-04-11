#include <math.h>
#include <iostream>
#include <ostream>
#include <set>

using namespace std;


template <typename Container>
void display(const Container &con){
    for(auto &it : con){
        cout << it << " ";
    }
    cout << endl;
}

class Point{
public:
    Point(int x, int y)
    :_x(x), _y(y)
    {}

    friend std::ostream &operator<<(ostream &os, const Point &p);

    friend bool operator<(const Point &p1, const Point &p2);

    friend struct PointCompare;

private:
    int _x;
    int _y;
};

std::ostream &operator<<(ostream &os, const Point &p){
    os << "(" << p._x << ", " << p._y << ")";
    return os;
}
bool operator<(const Point &p1, const Point &p2){
    if(p1._x == p2._x){
        return p1._y < p2._y;
    }
    return p1._x < p2._x;
}

struct PointCompare{
    bool operator()(const Point &p1, const Point &p2) const{
        if(p1._x == p2._x){
            return p1._y < p2._y;
        }
        return p1._x < p2._x;
    }
};

void test(){
    set<Point> spo = {  
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 5}
    };


    display(spo);
    
}

int main(){

    test();
    
    return 0;
}

