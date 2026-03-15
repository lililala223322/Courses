#include <stdio.h>

int StanOllie(int a, int b, int turn)   
{
    if (a < b) { int t = a; a = b; b = t; }
    if (b == 0) return !turn;      
    if (a >= 2 * b) return turn;   
    return StanOllie(b, a % b, !turn); 
}

int main(void)
{
    int C;
    if (scanf("%d", &C) != 1) return 0;
    for (int i = 0; i < C; ++i) {
        int m, n;
        scanf("%d %d", &m, &n);
        printf("%s wins\n", StanOllie(m, n, 1) ? "Stan" : "Ollie");
    }
    return 0;
}