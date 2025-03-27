#include <my_header.hpp>

// class Record
// {
// public: 
//     Record(string word, int frequency)
//     :_word(word)
//     ,_frequency(frequency)
//     {
//         
//     }
// 
// private:
// 	string _word;
// 	int _frequency;
// };
struct Record
{
    string _word;
    int _frequency;
};

class Dictionary
{
public:
    // 设置容器空间
    // 设置较大，避免频繁扩容
    Dictionary(int size)
    {   
        _dict.reserve(size);
    }

    // 
    void read(const string & filename){
        // 1.打开文件流
        fstream fs(filename);
        string line;
        // 2.不断获取每行字符
        while(getline(fs, line)){
            // 3.使用串流获取每个单词
            // 4.然后比较动态数组中的每个单词
            // 如果重复就+1
            // 没有就加入数组
            istringstream iss(line);
            string word;

            while(iss >> word){
                size_t i = 0;
                for ( ;i < _dict.size(); i++){
                    if(word == _dict[i]._word){
                        _dict[i]._frequency ++;
                        break;
                    }
                }
                // 循环结束后，若i等于当前字典大小，说明未找到单词
                if(i == _dict.size()){
                    _dict.push_back({word, 1});
                }
            }
        }
        fs.close();
    }
    // 
    void store(const string & filename){
        fstream ofs(filename);
        for(auto & st : _dict){
            ofs << st._word << " " << st._frequency << endl;
        }
        ofs.close(); 
    }

private:
    vector<Record> _dict;
};



void test(){
    Dictionary d1(10000);
    d1.read("The_Holy_Bible.txt");
    d1.store("Bible.txt");
}

int main(){

    test();

    return 0;
}

