#include <my_header.hpp>
#include <list>

// 题目：学生成绩管理系统
// 题目要求：
// 1 .制作一个学生成绩单管理系统
// 2 .将student自定义数据类型进行排序，student中属性有姓名、年龄、语文成绩，数学成绩，英语成绩
// 排序规则：按照总成绩sum进行降序，如果总成绩sum相同按照语文成绩进行降序
// 提示：熟悉list容器的基本操作：包括初始化、遍历、排序等等

class Student{
public:
    Student(string name, int age, int ch, int ma, int en) 
    {
        _name = name;
        _age = age;
        _chinese = ch;
        _math = ma;
        _english = en;
        _sum = ch + ma + en;
    }

public:
    string _name;  
    int _age;
    int _chinese;   
    int _math;   
    int _english;
    int _sum;

};


template <typename Container>
void display(const Container &con){
    /* for (auto &it : con){ */
    /*     cout << "name     " << it._name << endl */
    /*          << "chinese  " << it._chinese << endl */
    /*          << "math     " << it._math << endl */
    /*          << "english  " << it._english << endl */
    /*          << "sum      " << it._sum << endl; */
    /* } */
    cout << "姓名\t年龄\t语文\t数学\t英语\t总分" << endl;
    cout << "------------------------------------------------" << endl;
    for (auto& s : con) {
        cout << s._name << "\t" 
            << s._age << "\t"
            << s._chinese << "\t"
            << s._math << "\t"
            << s._english << "\t"
            << s._sum << endl;
    }
}

bool Compare(Student & st1, Student & st2){
    if (st1._sum == st2._sum) {
        return  st1._chinese > st2._chinese;	
    }else{
        return st1._sum > st2._sum;
    }
}


void test(){
    Student p1("杜雯菲", 15,88,77,95);
    Student p2("杜蚊分", 15,67,58,26);
    Student p3("李八八", 16,95,77,88);
    Student p4("赵二蛋", 14,86,75,68);
    Student p5("王小牛", 15,86,46,86);
    Student p6("张小哈", 16,89,57,68);

    list<Student> lit;

    lit.push_back(p1);
    lit.push_back(p2);
    lit.push_back(p3);
    lit.push_back(p4);
    lit.push_back(p5);
    lit.push_back(p6);


    display(lit);
    cout << "-----------------" << endl;
    lit.sort(Compare);  
    cout << "\n排序后：" << endl;
    display(lit);


}

int main(){

    test();

    return 0;
}

