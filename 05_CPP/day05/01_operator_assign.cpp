#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class Computer{
public:
    Computer(const char *brand, float price)
    :_brand(new char[strlen(brand)+1]())
     ,_price(price)
    {
        strcpy(_brand, brand);
        cout << "构造Computer(const char *, float)" << endl;
    }

    ~Computer(){
        if(this != nullptr){
            delete [] _brand;
        }
        cout << "析构Computer" << endl;
    }

    Computer (const Computer & rhs)
    :_brand(new char[strlen(rhs._brand) + 1]())
    ,_price(rhs._price)
    {
        strcpy(_brand, rhs._brand);
        cout << "拷贝构造" << endl;
    }

    Computer & operator = (const Computer & rhs)
    {
        if(this != rhs){
            delete [] _brand;
            _brand = new char[strlen(rhs_brand) + 1]();
            strcpy(_brand, rhs._brand);
            _price(rhs._price);
        }
        cout << "赋值构造" << endl;
        return *this;
    }

    void print(){
        cout << "brand" << _brand <<",price" << _price <<endl;
    }

private:
    char *_brand;
    float _price;
};

void test(){
    Computer c1("naifn", 13300);
    computer c2 = c1;
    c1.print();
    c2.print();
}

int main(){

    test();
    
    return 0;
}

