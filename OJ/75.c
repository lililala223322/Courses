#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100000
#define BUF_SIZE 0x1000000   /* 16 MB 输入缓冲，足够 1e5 个整数 */

long long nums[MAXN];
long long heap[MAXN];
int heapSize = 0;

/* ---------- 最小堆 ---------- */
void heapUp(int k) {
    while (k > 0) {
        int p = (k - 1) >> 1;
        if (heap[k] >= heap[p]) break;
        long long t = heap[k]; heap[k] = heap[p]; heap[p] = t;
        k = p;
    }
}
void heapDown(int k) {
    while (1) {
        int left  = (k << 1) + 1;
        int right = left + 1;
        int smallest = k;
        if (left  < heapSize && heap[left]  < heap[smallest]) smallest = left;
        if (right < heapSize && heap[right] < heap[smallest]) smallest = right;
        if (smallest == k) break;
        long long t = heap[k]; heap[k] = heap[smallest]; heap[smallest] = t;
        k = smallest;
    }
}
void heapPush(long long v) {
    heap[heapSize] = v;
    heapUp(heapSize++);
}
long long heapPop(void) {
    long long ret = heap[0];
    heap[0] = heap[--heapSize];
    heapDown(0);
    return ret;
}

int main(void) {
    static char buf[BUF_SIZE];
    /* 一次性读入整行 */
    if (!fgets(buf, sizeof(buf), stdin)) return 0;

    int n = 0;
    char *p = buf;
    while (*p) {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\n' || *p == 0) break;
        nums[n++] = strtoll(p, &p, 10);
    }

    long long sum = 1;
    int moveCnt = 0;

    for (int i = 0; i < n; ++i) {
        long long v = nums[i];
        if (v >= 0) {
            sum += v;
        } else {
            sum += v;
            heapPush(v);
            while (sum < 1 && heapSize > 0) {
                sum -= heapPop();
                ++moveCnt;
            }
            if (sum < 1) {
                printf("-1\n");
                return 0;
            }
        }
    }
    printf("%d\n", moveCnt);
    return 0;
}