#include <my_header.hpp>
#include <unordered_map>
#include <utility>
#include <list>

class LRU{
public:
    LRU(int capa)
    :_capa(capa)
    {}

    void put(int key, int value){
        auto it = _nm.find(key);
        if(it == _nm.end()){// _nm中查找不到，不在list中
            if(_nodes.size() == _capa){// 如果list满了
                auto deletenode = _nodes.back();
                _nm.erase(deletenode.first);        // 删除索引中的结点
                _nodes.pop_back();                  // list队列中的也删除
            }
                _nodes.push_front({key, value});
                _nm[key] = _nodes.begin(); 
        }else{//元素是存在的
            it->second->second = value;//更新value
            //将元素移动到list的最前面
            _nodes.splice(_nodes.begin(), _nodes, it->second);
        }
        

    }
    // 获取key
    int get(int key){
        // 查找是否存在
        auto it = _nm.find(key);
        if(it == _nm.end()){ // 不存在
            return -1;
        }
        // 存在
        // 将结点放到首位
        _nodes.splice(_nodes.begin(), _nodes, it->second);
        // 并返回value
        return it->second->second;
    }

    void print() const
    {
        for(auto &elem : _nodes)
        {
            cout << "(" << elem.first
                 << ", " << elem.second
                 <<")  ";
        }
        cout << endl;
    }
    
private:
    int _capa;
    list<pair<int, int>> _nodes;
    unordered_map<int, list<pair<int, int>>::iterator> _nm;
};



void test(){
    LRU lru(3);

    lru.put(1, 11);
    lru.print();

    cout << endl;
    lru.put(2, 22);
    lru.print();

    cout << endl;
    cout << "lru.get(1) = " << lru.get(1) << endl;
    lru.print();

    cout << endl;
    lru.put(3, 33);
    lru.print();

    cout << endl;
    lru.put(4, 44);
    lru.print();

    cout << endl;
    cout << "lru.get(2) = " << lru.get(2) << endl;
    lru.print();

    cout << endl;
    lru.put(3, 300);
    lru.print();
}

int main(){

    test();
    
    return 0;
}

