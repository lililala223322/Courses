#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBERS 8 
#define MAX_INPUT_LENGTH 100

int nums[MAX_NUMBERS];
int numsSize = 0;
int result[MAX_NUMBERS];
int used[MAX_NUMBERS];

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void backtrack(int depth) {
    if (depth == numsSize) {
        for (int i = 0; i < numsSize; i++) {
            printf("%d", result[i]);
            if (i < numsSize - 1) printf(" ");
        }
        printf("\n");
        return;
    }
    
    for (int i = 0; i < numsSize; i++) {
        if (used[i]) continue;

        if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;

        used[i] = 1;
        result[depth] = nums[i];

        backtrack(depth + 1);

        used[i] = 0;
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }

    input[strcspn(input, "\n")] = '\0';

    char *token = strtok(input, " ");
    while (token != NULL && numsSize < MAX_NUMBERS) {
        nums[numsSize++] = atoi(token);
        token = strtok(NULL, " ");
    }

    qsort(nums, numsSize, sizeof(int), compare);

    memset(used, 0, sizeof(used));

    backtrack(0);
    
    return 0;
}