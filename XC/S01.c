#include <stdio.h>

int main()
{
    char c;
    int N[4] ={0};//0空格 1数字 2字母 3其他
    while(c=getchar())
    {
        if (c==10) break;
        else if (c==32) N[0]++;
        else if (c>=48 && c<=57) N[1]++;
        else if ((c>=65 &&c<=90) || (c>=97 && c<=122)) N[2]++;
        else N[3]++;
    }
    printf("%d个空格,%d个数字,%d个字母,%d个其他字符",N[0],N[1],N[2],N[3]);
}