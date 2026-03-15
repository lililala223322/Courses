#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int shoppingOffers(int* price, int priceSize, int** special, int specialSize, int* specialColSize, int* needs, int needsSize) {
    int totalSize = 1;
    for (int i = 0; i < needsSize; i++) {
        totalSize *= (needs[i] + 1);
    }

    int* dp = (int*)malloc(totalSize * sizeof(int));

    for (int i = 0; i < totalSize; i++) {
        dp[i] = INT_MAX;
    }

    int* strides = (int*)malloc(needsSize * sizeof(int));
    strides[needsSize - 1] = 1;
    for (int i = needsSize - 2; i >= 0; i--) {
        strides[i] = strides[i + 1] * (needs[i + 1] + 1);
    }

    dp[0] = 0;
    for (int state = 0; state < totalSize; state++) {
        if (dp[state] == INT_MAX) continue;
        
        int* current = (int*)malloc(needsSize * sizeof(int));
        int temp = state;
        for (int i = 0; i < needsSize; i++) {
            current[i] = temp / strides[i];
            temp %= strides[i];
        }
        
        for (int i = 0; i < needsSize; i++) {
            if (current[i] < needs[i]) {
                int newState = state + strides[i];
                if (newState < totalSize) {
                    int newCost = dp[state] + price[i];
                    if (newCost < dp[newState]) {
                        dp[newState] = newCost;
                    }
                }
            }
        }
        
        for (int i = 0; i < specialSize; i++) {
            int* offer = special[i];
            int valid = 1;
            
            // 检查礼包是否适用
            for (int j = 0; j < needsSize; j++) {
                if (current[j] + offer[j] > needs[j]) {
                    valid = 0;
                    break;
                }
            }
            
            if (valid) {
                int newState = state;
                for (int j = 0; j < needsSize; j++) {
                    newState += offer[j] * strides[j];
                }
                
                if (newState < totalSize) {
                    int newCost = dp[state] + offer[needsSize];
                    if (newCost < dp[newState]) {
                        dp[newState] = newCost;
                    }
                }
            }
        }
        
        free(current);
    }
    
    // 目标状态是满足所有需求的状态
    int targetState = 0;
    for (int i = 0; i < needsSize; i++) {
        targetState += needs[i] * strides[i];
    }
    
    int result = dp[targetState];
    
    free(dp);
    free(strides);
    
    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    int* price = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &price[i]);
    }

    int specialSize;
    scanf("%d", &specialSize);

    int** special = (int**)malloc(specialSize * sizeof(int*));
    int* specialColSize = (int*)malloc(specialSize * sizeof(int));
    
    for (int i = 0; i < specialSize; i++) {
        special[i] = (int*)malloc((n + 1) * sizeof(int));
        for (int j = 0; j < n + 1; j++) {
            scanf("%d", &special[i][j]);
        }
        specialColSize[i] = n + 1;
    }

    int* needs = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &needs[i]);
    }

    int result = shoppingOffers(price, n, special, specialSize, specialColSize, needs, n);
    printf("%d\n", result);
    
    return 0;
}