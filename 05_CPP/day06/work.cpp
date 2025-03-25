#include <my_header.hpp>

class Student {
private:
    int _id;        // 学号
    string _name;   // 姓名
    int _age;       // 年龄

public:
    // 构造函数
    Student(int sid, const string & sname, int sage)
    : _id(sid)
    , _name(sname)
    , _age(sage) 
    {

    }

    // 拷贝构造函数
    Student(const Student & rhs)
    : _id(rhs._id)
      , _name(rhs._name)
      , _age(rhs._age) 
    {

    }

    // 赋值构造函数
    Student& operator=(const Student & rhs) {
        if (this != &rhs) {  // 防止自赋值
            _id = rhs._id;
            _name = rhs._name;
            _age = rhs._age;
        }
        return *this;
    }

    // 打印学生信息
    void printInfo() const {
        cout << "学号: " << _id << endl
             << "姓名: " << _name << endl
             << "年龄: " << _age << endl;
    }
};

int main() {
    // 创建原始学生对象
    Student s1(1001, "张三", 20);
    
    // 拷贝
    Student s2(s1); 
    
    // 赋值
    Student s3(1002, "李四", 22);
    s3 = s1;  

    // 输出结果
    cout << "原始对象: ";
    s1.printInfo();

    cout << "拷贝构造对象: ";
    s2.printInfo();

    cout << "赋值后对象: ";
    s3.printInfo();

    return 0;
}
