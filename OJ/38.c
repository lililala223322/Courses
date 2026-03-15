#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXR 1000
#define MAXC 1000

char grid[MAXR][MAXC];

int main(void) {
    /* 1. 用 fgets 原理动态读入整行 */
    char *line = NULL;
    size_t len = 0, cap = 0;
    int c;
    while ((c = getchar()) != EOF && c != '\n') {
        if (len + 1 >= cap) {
            cap = cap ? cap * 2 : 1024;
            line = realloc(line, cap);
        }
        line[len++] = (char)c;
    }
    if (line == NULL) return 0;
    line[len] = '\0';

    /* 2. 解析 */
    int rows = 0, cols = 0;
    char *p = line;
    while (*p) {
        if (*p == '\'') {
            char ch = *++p;
            if (rows == 0) cols++;
            grid[rows][cols - 1] = ch;
            p++;
        } else if (*p == '}') {
            rows++;
        }
        p++;
    }
    rows--;

    /* 3. 炸弹逻辑 */
    int maxKill = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] != 'S') continue;
            int kill = 0;
            for (int x = i - 1; x >= 0 && grid[x][j] != 'B'; --x)
                if (grid[x][j] == 'E') ++kill;
            for (int x = i + 1; x < rows && grid[x][j] != 'B'; ++x)
                if (grid[x][j] == 'E') ++kill;
            for (int y = j - 1; y >= 0 && grid[i][y] != 'B'; --y)
                if (grid[i][y] == 'E') ++kill;
            for (int y = j + 1; y < cols && grid[i][y] != 'B'; ++y)
                if (grid[i][y] == 'E') ++kill;
            if (kill > maxKill) maxKill = kill;
        }
    }

    printf("%d\n", maxKill);
    free(line);
    return 0;
}