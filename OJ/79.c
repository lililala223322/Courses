#include <stdio.h>
#include <stdlib.h>

#define MAXMN 1000000  
int buf[MAXMN];

typedef struct {
    int val;  
    int idx;  
} Node;

Node heap[MAXMN];
int heapsiz;

void push(Node x) {
    int i = heapsiz++;
    heap[i] = x;
    while (i) {
        int p = (i - 1) / 2;
        if (heap[p].val >= heap[i].val) break;
        Node t = heap[i]; heap[i] = heap[p]; heap[p] = t;
        i = p;
    }
}

Node pop(void) {
    Node ret = heap[0];
    heap[0] = heap[--heapsiz];
    int i = 0;
    while (1) {
        int l = 2 * i + 1, r = l + 1, big = i;
        if (l < heapsiz && heap[l].val > heap[big].val) big = l;
        if (r < heapsiz && heap[r].val > heap[big].val) big = r;
        if (big == i) break;
        Node t = heap[i]; heap[i] = heap[big]; heap[big] = t;
        i = big;
    }
    return ret;
}

int main(void) {
    int total = 0;
    while (scanf("%d", &buf[total]) == 1) ++total;

    int n = 0;
    for (int i = 0; i < total && buf[i] != '\n'; ++i) ++n; 
    int m = total / n;

    int *pos = calloc(m, sizeof(int));
    for (int i = 0; i < m; ++i) {
        Node x = { buf[i * n + n - 1], i };
        push(x);
        pos[i] = n - 1;
    }

    long long ans = 0;
    for (int day = 1; day <= total; ++day) {
        Node top = pop();
        ans += (long long)top.val * day;
        if (--pos[top.idx] >= 0) {
            Node nx = { buf[top.idx * n + pos[top.idx]], top.idx };
            push(nx);
        }
    }
    printf("%lld\n", ans);
    free(pos);
    return 0;
}