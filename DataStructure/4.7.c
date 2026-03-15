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


// 算法思路：很像虚位密码。即双指针遍历S和T，当S中出现T的首字母时T的指针开始随S的指针共同后移，
//          若T的指针到达末尾，则说明T在S中出现，则该T在S中的位置即为i-T.length+1，记录该位置。
//          重复上述操作，直到S被遍历完毕，则可得到T最后出现的位置。
//          ps.为省略无关代码，i和j均为无条件后加，又当S[i]!=T[j]时，可能存在S[i]=T[0]的情况，
//          故需判断S[i-1]是否等于T[0]，若是，则说明T[0]在S[i-1]的后面，故j置1，否则置0。
//          右侧的第二个输入样例就符合上述情况。   
void BFSearch(SqString S, SqString T) {
    int pos = -1;
    for (int i = 0, j = 0; i < S.length; )
    {
        if (S.data[i++] != T.data[j++]) {
            if (S.data[i-1] == T.data[0]) {
                j = 1;
            }
            else {
                j = 0;
            }
        }
        else {
            if (j == T.length) {
                pos = i-T.length+1;
            }
        }
    }
    if (pos == -1) {
        printf("T不在S中\n");
    }
    else {
        printf("T最后出现在S中第%d位\n", pos);
    }
}

// 测试函数
int main() {
    SqString S, T;
    char str1[100] = {0} , str2[100] = {0};
    printf("输入字符串S：");
    scanf("%s", &str1);
    printf("输入字符串T：");
    scanf("%s", &str2);

    StrAssign(&S, str1);
    StrAssign(&T, str2);

    BFSearch(S, T);

    return 0;
}