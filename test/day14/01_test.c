#include <my_header.h>


int main(void){
    
    //int num = 0x64656667;
    int num = 0x64656668;
    char *ch = (char *)&num;
    printf("%c\n",*ch);
    
    int num2 = htonl(num);
    char *ch2 = (char *)&num2;
    printf("%c\n",*ch2);
    return 0;
}

