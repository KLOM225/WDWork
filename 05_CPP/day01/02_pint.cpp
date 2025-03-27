#include <iostream>
#include <string.h>
using std::cout;
using std::endl;


class Computer {
public:
	Computer(const char * brand, double price)
	//: _brand(brand)
    : _brand(new char[strlen(brand) + 1]())
	, _price(price)
	{
        strcpy(_brand,brand);
    }
    
private:
	char * _brand;
	double _price;
};

void test0(){
    Computer pc("Apple",12000);
}

int main(){
    test0();
    return 0;
}
