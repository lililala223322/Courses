#include <stdio.h>
#include <stdlib.h>

int* countBits(int n, int* returnSize) {
    *returnSize = n + 1;
    int* bits = (int*)malloc((n + 1) * sizeof(int));
    bits[0] = 0;
    for (int i = 1; i <= n; i++) {
        bits[i] = bits[i >> 1] + (i & 1);
    }
    return bits;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int size;
    int* result = countBits(n, &size);
    
    for (int i = 0; i < size; i++) {
        printf("%d", result[i]);
    }
    printf("\n");
    
    free(result);
    return 0;
}