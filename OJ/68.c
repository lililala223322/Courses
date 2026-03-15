#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define OFFSET 100000 

bool canReorderDoubled(int* arr, int arrSize) {
    int count[200001] = {0}; 

    for (int i = 0; i < arrSize; i++) {
        count[arr[i] + OFFSET]++;
    }

    int* sorted = (int*)malloc(arrSize * sizeof(int));
    for (int i = 0; i < arrSize; i++) {
        sorted[i] = arr[i];
    }

    for (int i = 0; i < arrSize - 1; i++) {
        for (int j = 0; j < arrSize - i - 1; j++) {
            if (abs(sorted[j]) > abs(sorted[j + 1])) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < arrSize; i++) {
        int num = sorted[i];
        int idx = num + OFFSET;

        if (count[idx] == 0) continue;
        
        int target = 2 * num;
        int target_idx = target + OFFSET;

        if (target_idx < 0 || target_idx > 200000 || count[target_idx] == 0) {
            free(sorted);
            return false;
        }

        count[idx]--;
        count[target_idx]--;
    }
    
    free(sorted);
    return true;
}

int main() {
    int arr[30000];
    int count = 0;
    char ch;
    
    while (scanf("%d%c", &arr[count], &ch) == 2) {
        count++;
        if (ch == '\n') break;
    }

    if (canReorderDoubled(arr, count)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    return 0;
}