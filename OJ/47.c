#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXLINE 1024
#define MAXN    13

int cmpAbsDesc(const void *a, const void *b){
    int aa = *(const int*)a, bb = *(const int*)b;
    return abs(bb) - abs(aa); 
}

int main(void){
    char line[MAXLINE];
    int pos[MAXN], neg[MAXN];
    int posCnt = 0, negCnt = 0;

    if (!fgets(line, sizeof(line), stdin)) return 0;
    const char *sep = " \t\r\n";
    for (char *tok = strtok(line, sep); tok; tok = strtok(NULL, sep)){
        int v = atoi(tok);
        if (v > 0)        pos[posCnt++] = v;
        else if (v < 0)   neg[negCnt++] = v;
    }

    qsort(neg, negCnt, sizeof(int), cmpAbsDesc);

    long long prod = 1;
    int selected = 0;          

    for (int i = 0; i < posCnt; i++){
        prod *= pos[i];
        selected = 1;
    }

    int negSel = negCnt & ~1; 
    for (int i = 0; i < negSel; i++){
        prod *= neg[i];
        selected = 1;
    }

    if (selected)
        printf("%lld\n", prod);
    else {
        if (negCnt) {
            int best = INT_MIN;
            for (int i = 0; i < negCnt; i++)
                if (neg[i] > best) best = neg[i];
            printf("%d\n", best);
        }
        else {
            printf("0\n");
        }
    }

    return 0;
}