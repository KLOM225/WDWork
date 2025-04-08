#include <my_header.hpp> 

// 写时复制
class CowString{
public:
    CowString(const char *pstr)
    :_pstr(new char[strlen(pstr) + 1 + 4]() +4)
    ,_refcount(1)
    {
        strcpy(_pstr, pstr);
    }
    //拷贝构造函数
    CowString(const CowString & rhs)
    :_pstr(rhs._pstr), _refcount(rhs._refcount + 1)
    {
        //此时不仅拷贝出来的对象引用计数加1
        //被拷贝的对象引用计数也需要加1
        ++rhs._refcount;
    }


private:
    char *_pstr;
    int _refcount;
};



void test(){
    CowString s1("hello");
    CowString s2 = s1;
    CowString s3 = s1;
    CowString s4 = s1;
    CowString s5 = s1;

    CowString s6 = CowString("world");
}

int main(){

    test();
    
    return 0;
}

