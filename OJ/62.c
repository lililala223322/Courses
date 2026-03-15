#include <stdio.h>
#include <ctype.h>

#define MAX_NUM 100000  // 假设最多10万个数字

int freq[100000] = {0};  
int seen[100000] = {0};  

int main() {
    int num = 0;
    int c;
    int sum = 0;

    // 逐字符读取
    while ((c = getchar()) != EOF && c != '\n') {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } else if (c == ',') {
            // 处理前一个数字
            freq[num]++;
            if (!seen[num]) {
                sum += num;
                seen[num] = 1;
            }
            num = 0;
        }
    }

    freq[num]++;
    if (!seen[num]) {
        sum += num;
        seen[num] = 1;
    }

    for (int i = 0; i < 100000; i++) {
        if (freq[i] >= 1) {
            sum += 1;
        }
    }

    printf("%d\n", sum);
    return 0;
}