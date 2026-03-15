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

void maxEqualSub(SqString *S, SqString *T)
{
    // 特殊情况
    if (S->length < 2) {
        return;
    }

    /*
      思路：
      采用存储长度和单个字母的形式来记录单个等值子串。
      因为要寻找最长等值字串，所以需要记录目前的最长等值子串和正在记录的等值子串。
      单指针遍历字符串并记录起始字母，下一个字母相同则计数器加1，不同则记录当前子串并与最长子串比较，更新当前子串。
    */
    int max = 1, count = 1;
    char currentChar = S->data[0], maxChar = S->data[0];

    for (int i = 1; i <= S->length; i++)
    {
        if ( i!= S->length && currentChar == S->data[i]) {
            count++;
        }
        else {
            // 如果有更大的，则记录
            if (count > max) {
                max = count;
                maxChar = currentChar;
            }
            // 重新开始计数
            currentChar = S->data[i];
            count = 1;
        }
    }

    // 赋值
    for (int i = 0; i < max; i++)
    {
        T->data[i] = maxChar;
        T->length++;
    }
}

int main() {
    SqString S;
    char str[100] = {0};
    // 输入字符串
    scanf("%s", &str);
    StrAssign(&S, str);

    // 重置顺序并输出
    SqString T;
    maxEqualSub(&S, &T);
    if (T.length < 2) {
        printf("没有等值字串");
    }
    else {
        printf("最长等值字串为：");
        for (int i = 0; i < T.length; i++)
        {
            printf("%c",T.data[i]);
        }
        printf("，其长度为%d",T.length);
    }
    
}