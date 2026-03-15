#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAXN        15
#define MAXDEPTH    4
#define HASHSIZE    (1<<20)

int n;
int goal[MAXN];
int init[MAXN];
static int globalVersion = 1;   /* 从 1 开始，0 表示“空” */

/* 哈希表 */
typedef struct {
    uint64_t key;
    char     version;
} HashEnt;
static HashEnt ht[HASHSIZE];

static inline uint64_t encode(const int *a) {
    uint64_t x = 0;
    for (int i = 0; i < n; ++i) x = (x << 4) | (a[i] & 0xF);
    return x;
}
static inline int hashIdx(uint64_t x) {
    return (x * 0x9E3779B9u) & (HASHSIZE - 1);
}
static int hashVisited(uint64_t key) {
    int idx = hashIdx(key);
    while (ht[idx].key != 0 && ht[idx].key != key) idx = (idx + 1) & (HASHSIZE - 1);
    if (ht[idx].key == key && ht[idx].version == globalVersion) return 1;
    ht[idx].key     = key;
    ht[idx].version = globalVersion;
    return 0;
}

/* 启发式：断点数 / 2 */
static int h(const int *a) {
    int cnt = 0;
    for (int i = 0; i < n - 1; ++i)
        if (a[i] + 1 != a[i + 1]) ++cnt;
    return (cnt + 1) >> 1;
}

/* IDA* 搜索 */
static int dfs(int depth, int maxd, int *path, int preStart, int preEnd, int preIns) {
    if (depth + h(path) > maxd) return 0;
    if (hashVisited(encode(path))) return 0;

    /* 判目标 */
    int ok = 1;
    for (int i = 0; i < n; ++i)
        if (path[i] != goal[i]) { ok = 0; break; }
    if (ok) return 1;
    if (depth == maxd) return 0;

    int tmp[MAXN];
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            int len = r - l + 1;
            for (int p = 0; p <= n - len; ++p) {
                if (p >= l && p <= r + 1) continue;          /* 无效插入 */
                if (depth && l == preStart && r == preEnd && p == preIns) continue;

                /* 生成新状态 */
                int idx = 0;
                if (p <= l) {               /* 插入在 l 之前 */
                    for (int i = 0; i < p; ++i)        tmp[idx++] = path[i];
                    for (int i = l; i <= r; ++i)       tmp[idx++] = path[i];
                    for (int i = p; i < l; ++i)        tmp[idx++] = path[i];
                    for (int i = r + 1; i < n; ++i)    tmp[idx++] = path[i];
                } else {                    /* 插入在 r 之后 */
                    for (int i = 0; i < l; ++i)        tmp[idx++] = path[i];
                    for (int i = r + 1; i < p + len; ++i) tmp[idx++] = path[i];
                    for (int i = l; i <= r; ++i)       tmp[idx++] = path[i];
                    for (int i = p + len; i < n; ++i)  tmp[idx++] = path[i];
                }

                if (dfs(depth + 1, maxd, tmp, l, r, p)) return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    int T, T2;
    if (scanf("%d", &T) != 1) return 0;
    T2 = T;

    static int result[1000];
    for (int j = 0; T--; ) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%d", &init[i]);
            goal[i] = i + 1;
        }

        int sol = -1;
        for (int maxd = 0; maxd <= MAXDEPTH; ++maxd) {
            ++globalVersion;                   /* 逻辑清空哈希表 */
            if (dfs(0, maxd, init, -1, -1, -1)) {
                sol = maxd;
                break;
            }
        }
        if (sol >= 0) result[j++] = sol;
        else          result[j++] = -1;
    }

    for (int i = 0; i < T2; i++)
    {
        if (result[i] != -1)
            printf("%d\n", result[i]);
        else   
            printf("5 or more\n");
    }
    

    return 0;
}