#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Computer{
public:
    Computer(const char *brand, float price)
    :_brand(new char[strlen(brand) + 1]())
     ,_price(price)
    {
        strcpy(_brand, brand);
        cout << "Computer(const char *brand, price)" << endl;

    }
    
    ~Computer(){
        if(_brand){
            delete []_brand;
            _brand = nullptr;
        }
        cout << "~Computer()" << endl;
    }

    Computer(const Computer & rhs)
    :_brand(new char[strlen(rhs._brand) + 1]())
     ,_price(rhs._price)
    {
        strcpy(_brand, rhs._brand);
        cout << "Computer(const Computer & rhs)" << endl;
    }

    Computer & operator=(const Computer & rhs)
    {
        //自赋值
        //当不是自赋值时，先销毁回收原先操作数申请的空间
        if( this != &rhs ){
            delete []_brand;
            _brand = new char[strlen(rhs._brand) + 1]();
            strcpy(_brand, rhs._brand);
            _price = rhs._price;
        }
        cout << "Computer & operator = (const Computer & rhs)" << endl;
        //如果是自赋值则返回自身
        return *this;
    }



    void print(){
        cout << "brand" << _brand << ",price" <<_price << endl;        
    }
private:
    char * _brand;
    float _price;
};

void test(){
    //拷贝构造函数
    Computer c1("Apple", 12000);
    Computer c2 = c1;
}

void test2(){
    //赋值构造函数
    Computer c1("Apple", 12000);
    Computer c2("Mi", 5933);
    c2 = c1;
}
void test3(){
    Computer c2("Apple", 12000);
    c2 = c2;
    c2.print();
}


int main(){
    test();
    cout << "-----" << endl;
    test2();
    cout << "-----" << endl;
    test3();
    return 0;
}

