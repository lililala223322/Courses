#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100000

typedef struct {
    int diff;
    int r1;
    int r2;
} Fish;

int cmp(const void *a, const void *b) {
    Fish *f1 = (Fish *)a;
    Fish *f2 = (Fish *)b;
    return f2->diff - f1->diff;   // 从大到小
}

/* 从一行字符串中解析出整数数组，返回个数 */
int parse_line(int *arr, char *line) {
    int cnt = 0;
    char *tok = strtok(line, " \t\r\n");
    while (tok) {
        arr[cnt++] = atoi(tok);
        tok = strtok(NULL, " \t\r\n");
    }
    return cnt;
}

int main(void) {
    static int reward1[MAXN], reward2[MAXN];
    char line[4096];

    /* 读 reward1 */
    if (!fgets(line, sizeof(line), stdin)) return 0;
    int n = parse_line(reward1, line);

    /* 读 reward2 */
    if (!fgets(line, sizeof(line), stdin)) return 0;
    parse_line(reward2, line);

    /* 读 k */
    if (!fgets(line, sizeof(line), stdin)) return 0;
    int k = atoi(line);

    /* 构建 Fish 数组 */
    Fish fishes[MAXN];
    for (int i = 0; i < n; ++i) {
        fishes[i].r1 = reward1[i];
        fishes[i].r2 = reward2[i];
        fishes[i].diff = reward1[i] - reward2[i];
    }

    qsort(fishes, n, sizeof(Fish), cmp);

    int score = 0;
    for (int i = 0; i < n; ++i)
        score += (i < k) ? fishes[i].r1 : fishes[i].r2;

    printf("%d\n", score);
    return 0;
}