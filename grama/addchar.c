#include <stdio.h>
#include <string.h>//���ڿ� ���̺귯��
#include <stdlib.h>// itoa���
int main() {
    

    char str[30] = "score : ";
    int score = 300;
    char str2[30];
 
    //������ ���ڿ���
    itoa(score, str2, 10);

    
    strcat(str, str2);
    printf("%s", str);

    

 

     
    return 0;

}