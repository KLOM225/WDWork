#include <my_header.hpp>


class Complex{
public:
    Complex(int real, int image)
    :_real(real)
    ,_image(image)
    {

    }
    
    Complex operator + (Complex & rhs){
        
        int real = _real + rhs._real;
        int image = _image + rhs._image;
        return Complex(real, image);
    }

    void print(){
        cout << "_real=" << _real << ",_image=" <<_image << endl;
    }

private:
    int _real;
    int _image;
};



void test(){
    Complex c1(3,4), c2(5,6);
    Complex c3 = c1 + c2;
    c3.print();
}

int main(){

    test();
    
    return 0;
}

