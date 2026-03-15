#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char line[1 << 20];          /* 1 MB 缓冲区，足够 10^5 个数字 */
    if (!fgets(line, sizeof(line), stdin)) return 0;

    int  target[100000];
    int  n = 0;
    /* 用 strtok 按空格、Tab、换行切分 */
    for (char *tok = strtok(line, " \t\r\n"); tok;
              tok = strtok(NULL, " \t\r\n")) {
        target[n++] = atoi(tok);
    }

    /* 原算法 */
    int ops = target[0];
    for (int i = 1; i < n; ++i)
        if (target[i] > target[i - 1])
            ops += target[i] - target[i - 1];

    printf("%d\n", ops);
    return 0;
}