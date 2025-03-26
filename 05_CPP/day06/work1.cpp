#include <my_header.hpp>

class Computer{
public:
    Computer(string name, float price)
    :_name(name)
    ,_price(price)
    {
        _name = name;
        totallprice += price;
    }

    ~Computer(){
        totallprice -= _price;
    }

    Computer(const Computer & rhs)
    :_name(rhs._name)
    ,_price(rhs._price)
    {
        totallprice += rhs._price;
    }

    Computer & operator = (const Computer & rhs){
        if(this != &rhs){
            totallprice -= _price;
            totallprice += rhs._price;

        }
        return *this;
    }
    
    void gettotallprice(){
        cout <<  totallprice << endl;
    }

private:
    string _name;
    float _price;
    static float totallprice;
};
float Computer::totallprice = 0;

void test(){
    Computer c1("A",1200);
    c1.gettotallprice();
    Computer c2("B", 3000);
    c2.gettotallprice();
    Computer c3 = c2;
    c3.gettotallprice();
    c3 = c1;
    c3.gettotallprice();
}

int main(){

    test();
    
    return 0;
}

