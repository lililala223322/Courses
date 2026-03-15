#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_BITS 16
#define HASH_SIZE (1<<HASH_BITS)
#define HASH_MASK (HASH_SIZE-1)

static int *lakeId, *lakeLast;
static int *ans;
static int *dry;

static inline int hash(int lake) {
    return (lake * 0x9E3779B1) & HASH_MASK;
}

static int findOrAdd(int lake, int idx, int *found) {
    int h = hash(lake);
    while (1) {
        if (lakeId[h] == 0) {
            *found = 0;
            lakeId[h]   = lake;
            lakeLast[h] = idx;
            return h;
        }
        if (lakeId[h] == lake) {
            *found = 1;
            return h;
        }
        h = (h + 1) & HASH_MASK;
    }
}

static int pickDryDay(int *dry, int drySz, int pos) {
    int l = 0, r = drySz;
    while (l < r) {
        int m = (l + r) >> 1;
        if (dry[m] > pos) r = m;
        else              l = m + 1;
    }
    return (l == drySz ? -1 : l);
}

int* avoidFlood(int* rains, int rainsSize, int* returnSize) {
    memset(lakeId, 0, sizeof(lakeId));
    for (int i = 0; i < rainsSize; ++i) ans[i] = 1;

    int drySz = 0;
    for (int i = 0; i < rainsSize; ++i) {
        int lake = rains[i];
        if (lake > 0) {
            ans[i] = -1;
            int found;
            int h = findOrAdd(lake, i, &found);
            if (found) {
                int idx = pickDryDay(dry, drySz, lakeLast[h]);
                if (idx < 0) {
                    *returnSize = 0;
                    return NULL;
                }
                int d = dry[idx];
                ans[d] = lake;
                memmove(&dry[idx], &dry[idx + 1],
                        (drySz - idx - 1) * sizeof(int));
                --drySz;
                lakeLast[h] = i;
            }
        } else {
            dry[drySz++] = i;
        }
    }
    *returnSize = rainsSize;
    return ans;
}

int main(void)
{
    lakeId   = calloc(HASH_SIZE, sizeof(int));
    lakeLast = calloc(HASH_SIZE, sizeof(int));
    ans      = calloc(100000, sizeof(int));
    dry      = calloc(100000, sizeof( int));

    char *line = malloc(2000000);          
    if (!line || !fgets(line, 2000000, stdin)) return 0;

    int rains[100000], n = 0;
    char *p = line;
    while (*p) {
        while (*p==' '||*p==',') ++p;
        if (*p<'0'||*p>'9') break;
        rains[n++] = (int)strtol(p, &p, 10);
    }
    free(line);

    int returnSize;
    int *ret = avoidFlood(rains, n, &returnSize);

    if (returnSize == 0) printf("[]\n");
    else {
        printf("[%d", ret[0]);
        for (int i = 1; i < returnSize; ++i) printf(",%d", ret[i]);
        printf("]\n");
    }

    free(lakeId); free(lakeLast); free(ans); free(dry);
    return 0;
}