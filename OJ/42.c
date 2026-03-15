#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}

int main(void) {
    char line[10000];         
    if (!fgets(line, sizeof(line), stdin)) {  
        puts("0");
        return 0;
    }

    int arr[5000], n = 0;
    for (char *tok = strtok(line, " \t");
         tok != NULL;
         tok = strtok(NULL, " \t")) {
        arr[n++] = atoi(tok);   
    }

    if (n == 0) {
        printf("0\n");
        return 0;
    }
    
    if (n == 1) {
        printf("%d\n", arr[0]);
        return 0;
    }
    
    // 动态规划数组
    int dp[100];
    
    // 初始化
    dp[0] = arr[0];
    dp[1] = max(arr[0], arr[1]);
    
    // 填充dp数组
    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i-1], dp[i-2] + arr[i]);
    }
    
    printf("%d", dp[n-1]);
    
    return 0;
}