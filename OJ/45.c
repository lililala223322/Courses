#include <stdio.h>

int minOperations(int n) {
    int count = 0;
    while (n) {
        if (n & 1) {
            if ((n & 3) == 3) {  
                n++;
                count++;
            } else {
                n--;
                count++;
            }
        } else {
            n >>= 1;
        }
    }
    return count;
}

int main() {
    int n;
    scanf("%d",&n);
    printf("%d",minOperations(n));
    return 0;
}