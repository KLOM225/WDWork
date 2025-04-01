#include <my_header.hpp>

class A{
public:
    A(){
        cout << "A()" << endl;
    }

    ~A(){
        cout << "~A()" << endl;
    }

    void print(){
        cout << "A::print()" << endl;
    }


};

class B{
public:
    B(){
        cout << "B()" << endl;
    }

    ~B(){
        cout << "~B()" << endl;
    }

    void show(){
        cout << "B::show()" << endl;
    }

    void print(){
        cout << "B::print()" << endl;
    }
};

class C{
public:
    C(){
        cout << "C()" << endl;
    }

    ~C(){
        cout << "~C()" << endl;
    }
    void display(){
        cout << "C::display()" << endl;
    }

    void print(){
        cout << "C::print()" << endl;
    }
};

class D:
//public A,B,C
public A,
public B,
public C
{
public:
    D(){
        cout << "D()" << endl;
    }

    ~D(){
        cout << "~D()" << endl;
    }

    void print(){
        cout << "D::print()" << endl;
    }
};

void test(){
    D d;
    d.print();
    d.show();
    d.display();

}

int main(){

    test();
    
    return 0;
}

