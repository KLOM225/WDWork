#include <my_header.hpp>
#include <deque>
#include <algorithm>
#include <cstdlib>  // 包含 rand() 和 srand()
#include <ctime>    // 包含 time()（用于设置随机种子）
                    
/* 评委打分的例子： */
/* 要求：有五名选手ABfDE，10个评委打分，去掉最高分和最低分，求出每个选手的平均分。 */
/* 思路： 1.创建Person类，定义name，score成员属性；创建五名选手存放到vector容器中； */
/* 2.遍历vector容器，首先10个评委的打分存放到deque容器中，sort算法对分数排序，去掉最高最低分； */
/* 3.deque容器遍历，进行剩余分数的累加，求平均； */
/* 4.输出每个选手的姓名，成绩 */
//提示：还是容器vector与deque的基本使用


class Person{
public:
    Person(){}

    Person(const string name,const int score = 0)
        :_name(name)
         ,_score(score)
    {

    }

    void getscore(int socre){
        _score = socre;
    }
    void coutname(){
        cout << _name << endl ;
    }
    void print(){
        cout << _name << ": "<< _score << endl;
    }
private:
    string _name;
    int _score;
};



void test(){
    //Person A("A", 10), B("B", 15), C("C", 20), D("D",15), E("E",30);
    Person A("A"),B("B"),C("C"),D("D"),E("E");
    vector<Person> vec{A,B,C,D,E};
        srand(time(NULL)); 
    for (auto &it : vec){
        deque<int> score(10);
        
        /* cout << "输入10个评委的分数" << endl; */
        /* for(int i = 0; i < 10; ++i){ */
        /*     cout << i << ": "; */
        /*     cin >> scr; */
        /*     score.push_back(scr); */
        /* } */


        /* cout << "socre "; */ 
        /* it.Person::coutname() ; */
        for(int i = 0; i < 10; ++i){
            int src = rand() % 100;
            score.push_back(src);
        }
        sort(score.begin(), score.end());
        score.pop_front();
        score.pop_back();

        int avg = 0;
        for(auto &it : score){
            avg += it;
        }
        avg = avg / 8;
        it.Person::getscore(avg);
    }
    for(auto &it : vec){
        it.Person::print();
    }

}

int main(){

    test();

    return 0;
}

