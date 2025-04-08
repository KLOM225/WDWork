#include <my_header.hpp>


class Singleton{
public:
    static Singleton *getInstance(){
        if(_pInstance == nullptr){
            _pInstance = new Singleton();
        }
        return _pInstance;
    }
    
    static void destroy(){
        if(_pInstance){
            delete  _pInstance;
            _pInstance = nullptr;
        }
    }        

    void print(){
        cout << "Singleton::print" << endl;
    }


private:
    Singleton(){}

    ~Singleton(){}

    Singleton(const Singleton &rhs) = delete;
    Singleton & operator = (const Singleton &rhs) = delete;
    static Singleton *_pInstance;
};
Singleton *Singleton::_pInstance = nullptr;


void test(){
    cout << "hello" << endl;
}

int main(){

    test();
    
    return 0;
}

