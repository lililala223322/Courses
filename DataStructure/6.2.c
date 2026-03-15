#include <stdio.h>
#include <string.h>

// 核心算法：从右往左找，第一个匹配的就是最后一个
int lastLetter(char s[], char c, int pos)
{ 
    // -1退出
    if (pos == -1) {
        return -1;
    } else if (s[pos] == c) {
    // 找到了，返回位置
        return pos;
    } else {
    // 继续找
        return lastLetter(s, c, pos-1);
    }
}

int main()
{
    char s[100] = "Hello World";
    char c = 'l';
    printf("原字符串：%s\n", s);

    int pos = lastLetter(s, c, strlen(s)-1);

    printf("最后一个%c的位置：%d\n", c, pos+1);
    return 0;
}