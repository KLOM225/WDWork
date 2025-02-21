#include <stdio.h>
#include <ctype.h> // 用于 isalpha() 和 isdigit() 函数

int main() {
    char input[100];
    int letters = 0, digits = 0, spaces = 0;
    int i = 0;

    
    printf("请输入一行字符串: ");
    fgets(input, sizeof(input), stdin);

    while (input[i] != '\0') {
        if (isalpha(input[i])) {  
            letters++;
        } else if (isdigit(input[i])) {
            digits++;
        } else if (input[i] == ' ') {
            spaces++;
        }
        i++;
    }

    printf("字母数量: %d\n", letters);
    printf("数字数量: %d\n", digits);
    printf("空格数量: %d\n", spaces);

    return 0;
}

