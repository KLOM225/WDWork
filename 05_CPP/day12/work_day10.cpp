#include <my_header.hpp>
#include <map>

//词频统计的作业再用map容器去实现一次，体验一下使用vector/map时程序执行的速度

class Dictionary{
public:
    void read(string filename){
        ifstream ifs(filename);
        string line;
        while(getline(ifs, line)){
            istringstream iss(line);
            string str;
            while(iss >> str){
                ++ _dic[str];
            }
        }
        ifs.close();
    }

    void write(string filename){
        ofstream ofs(filename);
        auto it = _dic.begin();
        while(it != _dic.end()){
            ofs << it->first << " " << it->second << endl;
            it++;
        }
        ofs.close();
    }

private:
    map<string, int> _dic;
};


void test(){
    Dictionary dict;
    dict.read("The_Holy_Bible.txt");
    dict.write("bible.txt");
}

int main(){

    test();
    
    return 0;
}

