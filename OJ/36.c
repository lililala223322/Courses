#include <stdio.h>

#define MAX 100

int maxKilledEnemies(char grid[MAX][MAX], int rows, int cols) {
    int max = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 'S') {
                int count = 0;

                // 向上
                for (int x = i - 1; x >= 0; x--) {
                    if (grid[x][j] == 'B') break;
                    if (grid[x][j] == 'E') count++;
                }

                // 向下
                for (int x = i + 1; x < rows; x++) {
                    if (grid[x][j] == 'B') break;
                    if (grid[x][j] == 'E') count++;
                }

                // 向左
                for (int y = j - 1; y >= 0; y--) {
                    if (grid[i][y] == 'B') break;
                    if (grid[i][y] == 'E') count++;
                }

                // 向右
                for (int y = j + 1; y < cols; y++) {
                    if (grid[i][y] == 'B') break;
                    if (grid[i][y] == 'E') count++;
                }

                if (count > max) max = count;
            }
        }
    }

    return max;
}

int main() {
    char grid[MAX][MAX] = {
        {'E','E','S','S','S'},
        {'S','S','E','B','S'},
        {'S','E','B','S','E'},
        {'S','B','S','S','S'},
        {'S','E','S','B','E'}
    };

    int rows = 5;
    int cols = 5;

    int result = maxKilledEnemies(grid, rows, cols);
    printf("%d\n", result);  // 输出：4

    return 0;
}