#include <stdio.h>
#include <stdlib.h>


int reverseNumber(int num) {
    int reversed = 0;
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return reversed;
}

int main() {
    int n;
    scanf("%d",&n);
    for (int i = 1; i < n; i++)
    {
        if (i + reverseNumber(i) == n)
        {
            printf("True");
            return 0;
        }
    }
    printf("False");
        
}