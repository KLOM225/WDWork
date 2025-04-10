#include <my_header.hpp>
#include <set>


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



private:
    int _x;
    int _y;
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

