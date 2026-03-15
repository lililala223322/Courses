#include <stdio.h>
#include <stdlib.h>

#define MAX_K 60  

long long L[MAX_K];

void compute_lengths() {
    L[0] = 3;
    int k = 1;
    while (L[k-1] < 1e18) {  // 足够大
        L[k] = 2 * L[k-1] + (k + 3);
        k++;
    }
}

char find_char(long long N, int k) {
    if (k == 0) {
        // S(0) = "moo"
        if (N == 1) return 'm';
        else return 'o';
    }
    if (N <= L[k-1]) {
        return find_char(N, k-1);
    } else if (N == L[k-1] + 1) {
        return 'm';
    } else if (N <= L[k-1] + 1 + (k + 2)) {
        return 'o';
    } else {
        return find_char(N - (L[k-1] + 1 + (k + 2)), k-1);
    }
}

int main() {
    compute_lengths();
    long long N;
    scanf("%lld", &N);
    
    int k = 0;
    while (L[k] < N) {
        k++;
    }
    
    char ans = find_char(N, k);
    printf("%c\n", ans);
    return 0;
}