#include <stdio.h>

int main() {
    int numbers[100]; 
    int count = 0;   

    while (1) {
        int num;
        scanf("%d", &num);
        if (num == 0) {
            break; 
        }
        numbers[count++] = num; 
    }

    // 倒序输出
    for (int i = count - 1; i >= 0; i--) {
        printf("%d", numbers[i]);
        if (i > 0) {
            printf(" "); 
        }
    }

    return 0;
}