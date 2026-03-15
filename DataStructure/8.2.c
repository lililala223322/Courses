#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

void insertEdge(int matrix[][MAXSIZE], int i, int j, int weight)
{
    matrix[i][j] = weight;
    return;
}

/*
    核心思路：
    用邻接矩阵会简单很多，假设我们要找x的入边结点，那么令j=x，遍历i，weight不为0则有入边。
*/
void outEdge(int matrix[MAXSIZE][MAXSIZE], int x) {
    for (int i = 0; i < MAXSIZE; i++)
    {
        if (matrix[i][x] != 0) {
            printf("%d的入边结点为%d，权值为%d\n", x, i, matrix[i][x]);
        }
    }
    
}

int main()
{
    int matrix[MAXSIZE][MAXSIZE] = {0};

    insertEdge(matrix, 1, 2, 1);
    insertEdge(matrix, 1, 3, 2);
    insertEdge(matrix, 1, 5, 3);
    insertEdge(matrix, 2, 1, 3);
    insertEdge(matrix, 2, 5, 3);
    insertEdge(matrix, 3, 4, 4);
    insertEdge(matrix, 3, 1, 3);
    insertEdge(matrix, 3, 2, 3);
    insertEdge(matrix, 4, 2, 4);
    insertEdge(matrix, 4, 1, 3);
    insertEdge(matrix, 5, 3, 3);
    insertEdge(matrix, 5, 1, 4);

    outEdge(matrix, 1);

    return 0;
}