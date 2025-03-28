#include <my_header.hpp>


class Complex{
public:
    Complex(int real, int image)
    :_real(real)
    ,_image(image)
    {

    }

    
    friend Complex operator + (Complex & rhs1, Complex &rhs2);
    
    void print(){
        cout << "_real=" << _real << ",_image=" <<_image << endl;
    }

private:
    int _real;
    int _image;
};

    
    Complex operator + (Complex & rhs1, Complex &rhs2){
        
        int real = rhs1._real + rhs2._real;
        int image = rhs1._image + rhs2._image;
        return Complex(real, image);
    }


void test(){
    Complex c1(3,4), c2(5,6);
    Complex c3 = c1 + c2;
    c3.print();
}

int main(){

    test();
    
    return 0;
}

