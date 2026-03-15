#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXSIZE 100
#define TRUE 1
#define FALSE 0

typedef struct SqString{
    char data[MAXSIZE];
    int length;
} SqString;

// 将char赋给串s
void StrAssign(SqString *S, const char *chars) {
    int len = strlen(chars);
    if (len > MAXSIZE) len = MAXSIZE; // 防止越界
    strncpy(S->data, chars, len);
    S->length = len;
}

// 核心思路：单指针遍历并记录当前最大字符及其出现次数，若出现更大字符则重置计数为1
int CountMaxChar(SqString *S, char* maxChar)
{
    // 串长度为0、1、2为特殊情况。
    if ( S->length == 0 ) {
        return 0;
    }

    // 计数
    int count = 1;
    *maxChar = S->data[0];
    for (int i = 1; i < S->length; i++)
    {
        if ( *maxChar < S->data[i] ) {
            *maxChar = S->data[i];
            count = 1;
        }
        else if ( *maxChar == S->data[i] ) {
            count++;
        }
    }
    
    return count;
}

int main() {
    SqString S;
    char str[100] = {0};
    // 输入字符串
    scanf("%s", &str);
    StrAssign(&S, str);

    // 计数
    char maxChar;
    int count = CountMaxChar(&S, &maxChar);
    printf("%c最大且出现了%d次", maxChar, count);
}