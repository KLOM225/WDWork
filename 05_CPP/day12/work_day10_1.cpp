#include <iostream>
#include <cstring>
using namespace std;


// sso string
// sso：短字符串优化
// 如果字符串的长度小于15个字节，那么和string对象存储在一起
// 如果长度大于15个字节，那么才会真正地去开辟堆空间
// union(联合体)是一种特殊的数据结构，允许在同一内存位置存储不同类型的数据


class MyString{
public:
    MyString(){
        _size = 0;
    }

    MyString(const char *pstr){
        _size = strlen(pstr);
        if(_size <= 15){
            memset(_buffer._array, 0, 15);
            strcpy(_buffer._array, pstr);
        }else{
            _buffer._point = new char[strlen(pstr) + 1]();
            strcpy(_buffer._point, pstr);

        }
    }

    MyString(const MyString & rhs)
    {
        _size = rhs._size;
        if(_size <= 15){
            memset(_buffer._array, 0, 15);
            strcpy(_buffer._array, rhs._buffer._array);
        }else{
            _buffer._point = new char[strlen(rhs._buffer._point) + 1]();
            strcpy(_buffer._point, rhs._buffer._point);
        }
    }
    // 判断情况
    // 1.清空数组 / 指针
    // 2.判断rhs 大小，当size<15时复制到数组
    //                 当size > 15时 创建堆区
    MyString & operator = (const MyString & rhs){
        if(this != &rhs){
            if(_size <= 15){
                memset(_buffer._array, 0, 15);
            } else{
                delete [] _buffer._point;
                _buffer._point = nullptr;
            }

            if(rhs._size <= 15){
                strcpy(_buffer._array, rhs._buffer._array);
                _size = rhs._size;
            }else{
                _buffer._point = new char [strlen(rhs._buffer._point) + 1]();
                strcpy(_buffer._point, rhs._buffer._point); 
                _size = rhs._size;
            }
        }
        return *this;
    }

    ~MyString(){
        if(_size > 15){
            delete [] _buffer._point;
            _buffer._point = nullptr;
        }
    }

    size_t size()const {
        return _size;
    }

    const char * c_str() const {
        if(_size <= 15){
            return _buffer._array;
        }
        return _buffer._point;
    }


    union Buffer{
        char * _point;
        char _array[16];
    };
private:
    size_t _size;
    Buffer _buffer;
};

void test(){
    MyString s1("hello");
    MyString s2("safasdfuyhldkqyreq");
    cout << s1.c_str() << endl;
    cout << s1.size() << endl;
   
    cout << s2.c_str() << endl;
    cout << s2.size() << endl;
   
    MyString s3 = s1;
    MyString s4 = s2;
    cout << s3.c_str() << endl;
    cout << s4.c_str() << endl;

    cout << "======================" << endl;
    s3 = s2;

    cout << s1.c_str() << endl;
    cout << s2.c_str() << endl;
    MyString s5("hello,world");
    cout << s5.c_str() << endl;

    cout << (void *)s1.c_str() << endl;
    cout << (void *)s2.c_str() << endl;
    cout << (void *)s5.c_str() << endl;
    
}

int main(){

    test();

    return 0;
}

