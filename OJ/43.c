#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXV 100000        

int main(void)
{
    static char exist[MAXV + 1];  
    int nums[100000];
    int n = 0, maxv = 0;

    char line[1 << 20];
    if (!fgets(line, sizeof(line), stdin)) { puts("-1"); return 0; }
    for (char *tok = strtok(line, " \t\r\n"); tok; tok = strtok(NULL, " \t\r\n")) {
        int v = atoi(tok);
        nums[n++] = v;
        exist[v] = 1;
        if (v > maxv) maxv = v;
    }

    int ans = -1;
    int lim = (int)sqrt((double)maxv) + 2;   
    for (int i = 2; i <= lim; ++i) {
        if (!exist[i]) continue;             
        long long x = (long long)i * i;    
        int len = 1;
        while (x <= MAXV && exist[x]) {
            ++len;
            x *= x;                        
        }
        if (len >= 2 && len > ans) ans = len;
    }

    printf("%d\n", ans);
    return 0;
}