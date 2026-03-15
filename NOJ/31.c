#include <stdio.h>
 
void binary_expression(int n) {
    if (n == 0) {
        return;
    }
    if (n == 1) {
        printf("2(0)");
        return;
    }
    if (n == 2) {
        printf("2");
        return;
    }
 
    int k = 0;
    while ((1 << (k + 1)) <= n) {
        k++;
    }
 
    if (k == 1) {
        printf("2");
    } else {
        printf("2(");
        binary_expression(k);
        printf(")");
    }
 
    if (n - (1 << k) != 0) {
        printf("+");
        binary_expression(n - (1 << k));
    }
}
 
int main() {
    int n;
    scanf("%d", &n);
 
    binary_expression(n);
 
    return 0;
}