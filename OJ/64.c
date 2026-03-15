#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUM 5000
#define OFFSET MAX_SUM

int tallestBillboard(int* rods, int rodsSize) {
    if (rodsSize == 0) return 0;
    
    // dp数组：dp[i][diff]表示处理前i根钢筋，高度差为diff时的最大总高度
    int* dp = (int*)malloc((2 * MAX_SUM + 1) * sizeof(int));
    int* dp_prev = (int*)malloc((2 * MAX_SUM + 1) * sizeof(int));
    
    // 初始化
    for (int i = 0; i <= 2 * MAX_SUM; i++) {
        dp_prev[i] = -1;
    }
    dp_prev[OFFSET] = 0;  // 初始状态：高度差为0，总高度为0
    
    for (int i = 0; i < rodsSize; i++) {
        for (int j = 0; j <= 2 * MAX_SUM; j++) {
            dp[j] = dp_prev[j];
        }
        
        for (int j = 0; j <= 2 * MAX_SUM; j++) {
            if (dp_prev[j] < 0) continue;
            
            int rod = rods[i];
            
            // 将钢筋放在较高的一边（减少高度差）
            if (j - rod >= 0) {
                int new_diff = j - rod;
                dp[new_diff] = (dp[new_diff] > dp_prev[j] + rod) ? dp[new_diff] : dp_prev[j] + rod;
            }
            
            // 将钢筋放在较低的一边（可能增加或减少高度差）
            if (j + rod <= 2 * MAX_SUM) {
                int new_diff = j + rod;
                dp[new_diff] = (dp[new_diff] > dp_prev[j] + rod) ? dp[new_diff] : dp_prev[j] + rod;
            }
        }
        
        // 交换dp和dp_prev
        int* temp = dp;
        dp = dp_prev;
        dp_prev = temp;
    }
    
    int result = dp_prev[OFFSET] / 2;
    
    free(dp);
    free(dp_prev);
    
    return result >= 0 ? result : 0;
}

int main() {
    char input[1000];
    scanf("%s", input);
    
    // 解析输入
    int rods[60];
    int count = 0;
    char* token = strtok(input, ",");
    
    while (token != NULL) {
        rods[count++] = atoi(token);
        token = strtok(NULL, ",");
    }
    
    int result = tallestBillboard(rods, count);
    printf("%d\n", result);
    
    return 0;
}