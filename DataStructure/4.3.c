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


// 核心思路：
// 1. 遍历字符串，统计数字的个数为num，则运行后结果应为S[0:num-1]为数字，S[num:length-1]为小写字母
// 2. 取双指针i和j分别从S的0和num起算。取str暂存S并遍历，若为数字，则放到i处；若为小写字母，则放到j处。
void Algorithm_4_3(SqString *S)
{
    // 计数器
    int num = 0;
    char str[100] = {0};

    // 假设字符串符合题目要求，对数字进行计数
    for (int i = 0; i < S->length; i++)
    {
        if ( S->data[i] >= '0' && S->data[i] <= '9') {
            num++;
        }
        str[i] = S->data[i];
    }

    // 重新放置
    for (int i = 0, k = 0, j = num; i< S->length;)
    {
        if ( str[i] >= '0' && str[i] <= '9') {
            S->data[k++] = str[i++];
        }
        else {
            S->data[j++] = str[i++];
        }
    }

    return;
}

int main() {
    SqString S;
    char str[100] = {0};
    // 输入字符串
    scanf("%s", &str);
    StrAssign(&S, str);

    // 重置顺序并输出
    Algorithm_4_3(&S);
    printf("结果：");
    for (int i = 0; i < S.length; i++)
    {
        printf("%c", S.data[i]);
    }
    
}