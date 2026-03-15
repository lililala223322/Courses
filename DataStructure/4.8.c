#include <stdio.h>
#include <string.h>

// 反转字符串
void reverseString(char *str, int len) {
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

// 计算部分匹配表（前缀函数）
// 该函数用于构建子串的部分匹配表，以便在KMP算法中快速跳过不必要的匹配
void computeLPSArray(const char *t, int tLen, int *lps) {
    int len = 0; // 记录当前最长前缀后缀的长度
    lps[0] = 0;  // lps[0]总是0，因为单个字符没有真前缀和真后缀
    int i = 1;

    while (i < tLen) {
        if (t[i] == t[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1]; // 回退到前一个可能的最长前缀后缀长度
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP算法查找子串t在字符串s中第一次出现的位置
// 通过使用部分匹配表，避免重复比较，提高匹配效率
int kmpSearch(const char *s, const char *t) {
    int sLen = strlen(s);
    int tLen = strlen(t);
    int lps[tLen];

    computeLPSArray(t, tLen, lps); // 构建部分匹配表

    int i = 0; // 主串的索引
    int j = 0; // 子串的索引
    while (i < sLen) {
        if (t[j] == s[i]) {
            i++;
            j++;
        }

        if (j == tLen) {
            return i - j; // 找到匹配，返回起始位置
        } else if (i < sLen && t[j] != s[i]) {
            if (j != 0) {
                j = lps[j - 1]; // 利用部分匹配表跳过不必要的比较
            } else {
                i++;
            }
        }
    }
    return -1; // 未找到匹配
}

// 查找子串t在字符串s中最后一次出现的位置
// 通过反转字符串并利用KMP算法查找第一次出现的位置，再计算原字符串中的位置
int findLastOccurrence(const char *s, const char *t) {
    int sLen = strlen(s);
    int tLen = strlen(t);

    // 创建反转字符串
    char reversedS[sLen + 1];
    char reversedT[tLen + 1];
    strcpy(reversedS, s);
    strcpy(reversedT, t);
    reverseString(reversedS, sLen);
    reverseString(reversedT, tLen);

    // 使用KMP查找反转后的t在反转后的s中的第一次出现位置
    int reversedPosition = kmpSearch(reversedS, reversedT);

    if (reversedPosition == -1) {
        return -1; // 未找到
    }

    // 计算原字符串中t最后一次出现的位置
    return sLen - (reversedPosition + tLen) + 1;
}

int main() {
    char s[100] = {0}, t[100] = {0};
    printf("输入s: ");
    scanf("%s", s);
    printf("输入t: ");
    scanf("%s", t);

    int position = findLastOccurrence(s, t);
    if (position != -1) {
        printf("子串最后一次出现的位置是: %d\n", position); // 输出位置，从0开始计数
    } else {
        printf("子串未找到。\n");
    }
    return 0;
}