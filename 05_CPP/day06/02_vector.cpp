#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

void test() {
    // 空vector
    vector<int> num;
    cout << num.size() << endl;        

    // 包含10个默认初始化为0的元素
    vector<int> num2(10);
    cout << num2.size() << endl;       
    cout << num2[0] << endl;           

    // 包含10个值为20的元素
    vector<int> num3(10, 20);
    cout << num3.size() << endl;       
    cout << num3[0] << endl;           

    // 列表初始化
    vector<int> num4{1, 2, 3, 4, 5};   

    // 迭代器范围构造（排除最后一个元素）
    vector<int> num5(num4.begin(), num4.end() - 1); 
    
    // 修正变量名并添加输出
    cout << num5.size() << endl;   
    cout << "numbers5[3]: " << num5[3] << endl;  
    cout << "numbers5[2]: " << num5[2] << endl;  
}  

int main() {
    test();
    return 0;
}
