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

// 在串S的第pos个字符之前插入串T
bool StrInsert(SqString *S, int pos, const SqString *T) {
    if (pos < 1 || pos > S->length + 1 || S->length + T->length > MAXSIZE) return FALSE;
    for (int i = S->length - 1; i >= pos - 1; i--) {
        S->data[i + T->length] = S->data[i];
    }
    for (int i = 0; i < T->length; i++) {
        S->data[pos - 1 + i] = T->data[i];
    }
    S->length += T->length;
    return TRUE;
}

// 从串S中删除第pos个字符起长度为len的子串
bool StrDelete(SqString *S, int pos, int len) {
    if (pos < 1 || pos > S->length || len < 0 || pos + len - 1 > S->length) return FALSE;
    for (int i = pos - 1 + len; i < S->length; i++) {
        S->data[i - len] = S->data[i];
    }
    S->length -= len;
    return TRUE;
}

// 由串T复制得串S
void StrCopy(SqString *S, const SqString *T) {
    StrAssign(S, T->data); // 使用StrAssign简化实现
}

// 若串S为空串，则返回TRUE,否则返回FALSE
bool StrEmpty(const SqString *S) {
    return S->length == 0;
}

// 若S>T,则返回值大于0;如S=T,则返回值0;若S<T,则返回值小于0
int StrCompare(const SqString *S, const SqString *T) {
    return strcmp(S->data, T->data);
}

// 返回串S的长度，即串S中的字符个数
int StrLength(const SqString *S) {
    return S->length;
}

// 将S清为空串
void StrClear(SqString *S) {
    S->length = 0;
}

// 将串T的值连接在串S的后面
bool StrCat(SqString *S, const SqString *T) {
    if (S->length + T->length > MAXSIZE) return FALSE;
    strncpy(S->data + S->length, T->data, T->length);
    S->length += T->length;
    return TRUE;
}

// 用Sub返回串S的第pos个字符起长度为len的子串
bool SubString(SqString *Sub, const SqString *S, int pos, int len) {
    if (pos < 1 || pos > S->length || len < 0 || pos + len - 1 > S->length) return FALSE;
    for (int i = 0; i < len; i++) {
        Sub->data[i] = S->data[pos - 1 + i];
    }
    Sub->length = len;
    return TRUE;
}

int CountMaxChar(SqString *S, char* maxChar)
{
    // 串长度为0、1、2为特殊情况。
    if ( S->length == 0 ) {
        return 0;
    }
    else if ( S->length < 3 ) {
        return 1;
    } 

    // 计数思路：记录当前最大字符及其出现次数，出现更大字符则重置count
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

// 测试函数
int main() {
    SqString S;
    char str[100] = {0};
    scanf("%s", &str);
    StrAssign(&S, str);
    char maxChar;
    int count = CountMaxChar(&S, &maxChar);
    printf("%c最大且出现了%d次", maxChar, count);
}