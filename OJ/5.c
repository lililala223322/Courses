#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#define MAX 1000

bool covered[MAX][MAX] = {false};

int main() {
    int n;
    scanf("%d", &n);
    
    int total = 0;
    for (int s = 0; s < n; s++) {
        int x, y, r;
        scanf("%d %d %d", &x, &y, &r);
        
        int left = x - r;
        int right = x + r;
        int bottom = y - r;
        int top = y + r;
        
        for (int i = left; i <= right; i++) {
            for (int j = bottom; j <= top; j++) {
                if (i < 0 || j < 0 || i >= MAX || j >= MAX) continue;
                int dx = i - x;
                int dy = j - y;
                if ( abs(dx) + abs(dy) < r || dx*dx + dy*dy <= r*r) {
                    if (!covered[i][j]) {
                        covered[i][j] = true;
                        total++;
                    }
                }
            }
        }
    }
    
    printf("%d\n", total);
    return 0;
}