#include <my_header.hpp>

class Person{
public:
    Person(const char *name, int age)
    :_name(new char[strlen(name) + 1]())
    ,_age(age)
    {        
        strcpy(_name, name);
    }
    
    ~Person(){
        if(_name){
            delete [] _name;
            _name = nullptr;
        }
    }

    Person (const Person & rhs)
    :_name(new char[strlen(rhs._name) + 1]())
    ,_age(rhs._age)
    {
        strcpy(_name, rhs._name);
    }

    Person & operator = ( const Person & rhs){
        if(this != &rhs){
            delete [] _name;
            _name = new char[strlen(rhs._name) + 1]();
            strcpy(_name, rhs._name);
            _age = rhs._age;
        }
        return *this;
    }

    void display(){

        cout << "name" << _name << ", age" << _age<< endl;
        
    }

private:
    char *_name;
    int _age;

};

class Employee
:public Person
{
public: 
    Employee(const char * name, int age, const char * depart, double salary)
    :Person(name,age)
    ,_depart(new char[strlen(depart) + 1]())
    ,_salary(salary)
    {
        strcpy(_depart, depart);
        _totalSalary += salary;
        ++_totalNum;
    }
    
    Employee(const Employee &rhs)
    :Person(rhs)
    ,_depart(new char[strlen(rhs._depart) + 1]())
    ,_salary(rhs._salary)
    {
        strcpy(_depart, rhs._depart);
         _totalSalary += rhs._salary;
        ++_totalNum;
    }   

    Employee &operator = (const Employee & rhs){
        if(this != &rhs){
            Person::operator=(rhs);
             _totalSalary -= rhs._salary;
        
            delete [] _depart;
            _depart = new char[strlen(rhs._depart) + 1]();
            strcpy(_depart, rhs._depart);
            _salary = rhs._salary;
             _totalSalary += rhs._salary;

        }
        return *this;
    }

    ~Employee(){
        if(_depart){
            delete [] _depart;
            _depart = nullptr;
        }
    }
    
    void display(){
        Person::display();
        cout << "depart" << _depart << "  salary" << _salary << endl;
    }

    static double getAvgSalary(){
        return _totalSalary / _totalNum;
    }

private:
    char * _depart;
    float _salary;
    static double _totalSalary;
    static int _totalNum;
};
double Employee::_totalSalary = 0;
int Employee::_totalNum = 0;


void test(){
    Employee A("zhangsan", 23, "it", 9000);
    Employee B("lisi", 23, "it", 7000);
    cout << Employee::getAvgSalary() << endl;
    Employee C = A;

    cout << Employee::getAvgSalary() << endl;

    C = B;
    cout << Employee::getAvgSalary() << endl;
}
 

int main(){

    test();
    
    return 0;
}

