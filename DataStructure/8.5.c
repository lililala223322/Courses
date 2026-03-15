#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100

void insertEdge(int matrix[][MAXSIZE], int i, int j, int weight)
{
    matrix[i][j] = weight;
    return;
}

/*
    核心思路：
    假设图有向，寻找i到j的路径广度搜索即分开来递归搜索
    即根据输入的起点把每条边的终点递归调用
    因为只判断路径有无，所以无需记录节点
    但不记录可能会掉入死循环，所以得记个数，保证路径长度不会超过2 * n
    函数返回值为布尔值取交集，即有一条路即可返回true
*/

bool hasPath(int matrix[][MAXSIZE], int i, int j, int n, int count) {
    // 找到了
    if (matrix[i][j] != 0) {
        return true;
    }

    // 
    if (count > 2 * n) {
        return false;
    }

    for (int k = 0; k <= n; k++)
    {
        // 递归调用
        if (k != i && k != j &&  matrix[i][k] != 0) {
            return false || hasPath(matrix, k, j, n, count+1);
        }
    }
    
    
}

int main()
{
    int matrix[MAXSIZE][MAXSIZE] = {0};

    insertEdge(matrix, 1, 2, 1);
    insertEdge(matrix, 2, 3, 2);
    insertEdge(matrix, 3, 1, 3);
    insertEdge(matrix, 4, 5, 3);

    if (hasPath(matrix, 1, 5, 5, 0)) {
        printf("1到5有路径\n");
    }
    else {
        printf("1到5无路径\n");
    }

    if (hasPath(matrix, 1, 3, 5, 0)) {
        printf("1到3有路径\n");
    }
    else {
        printf("1到3无路径\n");
    }

    return 0;
}