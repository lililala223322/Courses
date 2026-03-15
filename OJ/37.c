#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 比较函数：先按宽度升序，宽度相同按高度降序
int cmp(const void *a, const void *b) {
    int *aa = *(int **)a;
    int *bb = *(int **)b;
    if (aa[0] != bb[0]) {
        return aa[0] - bb[0];
    } else {
        return bb[1] - aa[1];
    }
}

// 二分查找：在 tails 中找到第一个 >= x 的位置
int bisearch(int *tails, int len, int x) {
    int left = 0, right = len - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (tails[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

int maxEnvelopes(int** envelopes, int envelopesSize, int* envelopesColSize) {
    if (envelopesSize == 0) return 0;
    
    // 排序
    qsort(envelopes, envelopesSize, sizeof(int *), cmp);
    
    // 提取高度数组
    int *heights = malloc(envelopesSize * sizeof(int));
    for (int i = 0; i < envelopesSize; i++) {
        heights[i] = envelopes[i][1];
    }
    
    // LIS 动态规划 + 二分
    int *tails = malloc(envelopesSize * sizeof(int));
    int len = 0;
    
    for (int i = 0; i < envelopesSize; i++) {
        int pos = bisearch(tails, len, heights[i]);
        if (pos == len) {
            tails[len++] = heights[i];
        } else {
            tails[pos] = heights[i];
        }
    }
    
    free(heights);
    free(tails);
    return len;
}

// 解析输入字符串，返回二维数组和长度
void parseInput(char *s, int ***envelopes, int *size) {
    int count = 0;
    char *p = s;
    while (*p) {
        if (*p == '[') {
            if (*(p+1) >= '0' && *(p+1) <= '9') {
                count++;
            }
        }
        p++;
    }
    *size = count;
    
    int **envs = malloc(count * sizeof(int *));
    for (int i = 0; i < count; i++) {
        envs[i] = malloc(2 * sizeof(int));
    }
    
    // 解析数字
    p = s;
    int idx = 0;
    while (*p) {
        if (*p == '[' && *(p+1) >= '0' && *(p+1) <= '9') {
            p++; // 跳过 [
            // 第一个数字
            int num1 = 0;
            while (*p >= '0' && *p <= '9') {
                num1 = num1 * 10 + (*p - '0');
                p++;
            }
            // 跳过逗号
            p++;
            // 第二个数字
            int num2 = 0;
            while (*p >= '0' && *p <= '9') {
                num2 = num2 * 10 + (*p - '0');
                p++;
            }
            envs[idx][0] = num1;
            envs[idx][1] = num2;
            idx++;
        } else {
            p++;
        }
    }
    
    *envelopes = envs;
}

int main() {
    char input[1000];
    fgets(input, sizeof(input), stdin);
    
    int **envelopes = NULL;
    int size = 0;
    parseInput(input, &envelopes, &size);
    
    int colSize = 2;
    int result = maxEnvelopes(envelopes, size, &colSize);
    printf("%d\n", result);
    
    // 释放内存
    for (int i = 0; i < size; i++) {
        free(envelopes[i]);
    }
    free(envelopes);
    
    return 0;
}