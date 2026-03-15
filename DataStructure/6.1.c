#include <stdio.h>
#include <string.h>

// 核心算法：每次调用将head与对应的尾字母交换，然后head++再次调用该函数。
void stringReverse(char s[], int head)
{
    int tail = strlen(s) - head - 1;
    if (head <= tail) {
        char temp = s[head];
        s[head] = s[tail];
        s[tail] = temp;
        printf("逆置过程：%s\n", s);
    }
    // 递归调用
    if (tail - head > 1) {
        stringReverse(s, head + 1);
    }
}

int main()
{
    char s[100] = "Hello World";
    printf("原字符串：%s\n", s);
    stringReverse(s, 0);
    printf("反字符串：%s\n", s);
    return 0;
}