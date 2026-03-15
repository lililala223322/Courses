#include <stdio.h>
#include <math.h>

int countConsecutiveSums(int n) {
    int count = 0;
    
    // 连续整数列的长度为k，首项为a
    // 和为：k*a + k*(k-1)/2 = n
    // 所以：k*a = n - k*(k-1)/2
    // a必须是正整数，所以 n - k*(k-1)/2 > 0 且能被k整除
    
    for (int k = 1; k * (k - 1) / 2 < n; k++) {
        int numerator = n - k * (k - 1) / 2;
        if (numerator <= 0) break;
        
        if (numerator % k == 0) {
            int a = numerator / k;
            if (a > 0) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int result = countConsecutiveSums(n);
    printf("%d\n",result);
    
    return 0;
}