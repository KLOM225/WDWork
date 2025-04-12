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

    double getDistance() const
    {
        /* sqrt(pow(_ix, 2) + pow(_iy, 2)); */
        return hypot(_x, _y);
    }

    int getX() const
    {
        return _x;
    }

    int getY() const
    {
        return _y;
    }

    ~Point()
    {

    }


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
    if(p1.getDistance() < p2.getDistance()){
        return true;
    }else if(p1.getDistance() == p2.getDistance()){
        if(p1._x < p2._x){
            return true;
        }else if(p1._x == p2._x){
            if(p1._y < p2._y){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }

}

struct PointCompare{
    bool operator()(const Point &p1, const Point &p2) const{

        if(p1.getDistance() < p2.getDistance()){
            return true;
        }else if(p1.getDistance() == p2.getDistance()){
            if(p1._x < p2._x){
                return true;
            }else if(p1._x == p2._x){
                if(p1._y < p2._y){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
};

namespace std{
template<>
struct less<Point>{

    bool operator()(const Point &p1, const Point &p2) const{
        if(p1.getDistance() < p2.getDistance()){
            return true;
        }
        else if(p1.getDistance() == p2.getDistance()){
            if(p1.getX() < p2.getX()){
                return true;
            }else if(p1.getX() == p2.getX()){
                if(p1.getY() < p2.getY()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }

    }
};
}

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

