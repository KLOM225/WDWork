#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class String 
{
public:
    String()
        :_pstr(nullptr)
    {

    }

    String(const char *pstr)
        :_pstr(new char[strlen(pstr) + 1]())
    {
        strcpy(_pstr, pstr);

    }

    String(const String & rhs)
        :_pstr(new char[strlen(rhs._pstr) + 1]())
    {
        strcpy(_pstr, rhs._pstr);
    }

    ~String(){
        if(_pstr){
            delete  [] _pstr;
            _pstr = nullptr;
        }

    }

    // 赋值运算符
    String & operator = (const String &rhs){
        if(this != &rhs){
            delete  [] _pstr;
            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
        }
        return *this;
    }

    String &operator=(const char *pstr){
        String str(pstr);
        *this = str;
        return *this;
    }

    String &operator+=(const String &rhs){
        char * temp = new char[strlen(_pstr) + strlen(rhs._pstr) + 1]();
        strcpy(temp, _pstr);
        strcat(temp, rhs._pstr);
        delete  [] _pstr;
        _pstr = temp;
        return *this;
    }

    String &operator+=(const char *rhs){
        String str(rhs);
        *this += str;
        return *this;
    }


    char &operator[](std::size_t index){
        if(index < size()){
            return _pstr[index];
        }else{
            static char nullchar = '\0';
            return nullchar;
        }
    }

    const char &operator[](std::size_t index) const{
        if(index < size()){
            return _pstr[index];
        }else{
            static char nullchar = '\0';
            return nullchar;
        }
    }



    std::size_t size() const{
        return strlen(_pstr);
    }

    const char* c_str() const{
        return _pstr;
    }

    friend bool operator==(const String & str1, const String &str2){
        return (strcmp(str1._pstr, str2._pstr) == 0);
    }

    friend bool operator!=(const String &str1, const String &str2){
        return (strcmp(str1._pstr, str2._pstr) != 0);
    }

    friend bool operator<(const String &str1, const String &str2){
        return (strcmp(str1._pstr, str2._pstr) < 0);
    }

    friend bool operator>(const String &str1, const String &str2){
        return (strcmp(str1._pstr, str2._pstr) > 0);
    }

    friend bool operator<=(const String &str1, const String &str2){
        return (strcmp(str1._pstr, str2._pstr) <= 0);
    }

    friend bool operator>=(const String &str1, const String &str2){
        return (strcmp(str1._pstr, str2._pstr) >= 0);
    }

    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

private:
    char * _pstr;
};

std::ostream &operator<<(std::ostream &os, const String &s){
    if(s._pstr){
        os << s._pstr;
    } 
    return os;
}

std::istream &operator>>(std::istream &is, String &s){
    if(s._pstr){
        delete [] s._pstr;
    }
    vector<char> input;
    char ch;
    while((ch = is.get()) != '\n'){
        input.push_back(ch);
    }
    char * temp = new char[input.size() + 1]();
    strncpy(temp, input.data(), input.size());
    s._pstr = temp;
    return is;
}


String operator+(const String &str1, const String &str2){
    String temp(str1);
    temp += str2; 
    return temp;
}

String operator+(const String &str, const char *pstr){
    String temp(str);
    temp += pstr; 
    return temp;

}

String operator+(const char *pstr, const String &str){
    String temp(str);
    temp += pstr; 
    return temp;

}

void test(){

}

int main(){
    return 0;
}
