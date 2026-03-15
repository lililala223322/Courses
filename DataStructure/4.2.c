#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXSIZE 100

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

bool isStrReverse(SqString *S)
{
    // 算法思路：双指针分别从头和尾向串中央行进，并保证指针所指向的内容保持一致
    //          循环条件设为i<j可有效解决串长度为单数或双数的分支问题
    for (int i = 0, j = S->length-1; i < j; i++, j--)
    {
        if (S->data[i] != S->data[j]) {
            return false;
        }
    }
    
    return true;
}

int main() {
    SqString S;
    char str[100] = {0};
    // 输入字符串
    scanf("%s", &str);
    StrAssign(&S, str);

    // 判断
    if ( isStrReverse(&S) ) {
        printf("%s是回文字符串", str);
    }
    else {
        printf("%s不是回文字符串", str);
    }

}