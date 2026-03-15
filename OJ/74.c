#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int zs;
    int ls;
    int sum;
} Block;

int compare(const void *a, const void *b) {
    Block *ba = (Block *)a;
    Block *bb = (Block *)b;
    return bb->sum - ba->sum;
}

int main() {
    int zsValues[100000];
    int lsValues[100000];
    int n = 0;

    while (scanf("%d", &zsValues[n]) == 1) {
        n++;
        if (getchar() == '\n') break;
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &lsValues[i]);
    }
    
    Block blocks[100000];
    for (int i = 0; i < n; i++) {
        blocks[i].zs = zsValues[i];
        blocks[i].ls = lsValues[i];
        blocks[i].sum = zsValues[i] + lsValues[i];
    }
    
    qsort(blocks, n, sizeof(Block), compare);
    
    int zsScore = 0, lsScore = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) { // 张三的回合
            zsScore += blocks[i].zs;
        } else { // 李四的回合
            lsScore += blocks[i].ls;
        }
    }
    
    if (zsScore > lsScore) {
        printf("1\n");
    } else if (zsScore < lsScore) {
        printf("-1\n");
    } else {
        printf("0\n");
    }
    
    return 0;
}