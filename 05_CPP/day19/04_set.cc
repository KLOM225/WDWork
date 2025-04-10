#include <my_header.hpp>
#include <set>
#include <utility>

//set的基本特征

template <typename Container>
void display(const Container &con){
    for(auto &elme : con){
        cout << elme << " ";
    }
    cout << endl;
}

void test(){
    //set的基本特征
    //1、存放的可以key类型，key值是唯一的，不能重复
    //2、默认情况下，会按照key值升序排列
    //3、底层使用的是红黑树
    
    set<int> num = {1, 2, 3, 5, 7, 6, 5, 4, 3, 9};
    /* set<int, std::greater<int>> number = {1, 2, 3, 5, 8, 7, 6, 5, 4, 3, 9}; */
    display(num);

    cout << endl << "set的查找操作" << endl;
    size_t cnt = num.count(4);
    cout << "cnt = " << cnt << endl;
    
    /* set<int>::iterator it = num.find(7); */
    auto it = num.find(7);
    if(it != num.end()){
        cout << "该元素存在set中 " << *it << endl;
    }
    else
    {
        cout << "该元素不存在set中" << endl;
    }
        
    cout << endl << "set的插入操作" << endl;
    /* pair<set<int>::iterator, bool> ret = num.insert(8); */
    auto ret = num.insert(8);
   
    if(ret.second)
    {
        cout << "插入成功了 " << *ret.first << endl;
    }
    else
    {
        cout << "插入失败了, 该元素已经存在set中" << endl;
    }
    display(num);
    
    cout << endl << "set不支持下标" << endl;

    it = num.begin();
    it++;
    cout << "*it = " << *it << endl;
    /* *it = 1;//error */
}

int main(){

    test();
    
    return 0;
}

