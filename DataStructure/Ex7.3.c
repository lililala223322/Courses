#include <stdio.h>
#include <stdlib.h>

#define MAXVEX 100
#define INFINITY 10000

void ShortestPath_Floyd(int n, int G[MAXVEX][MAXVEX], int D[MAXVEX][MAXVEX]) {
    int v, w, k;
    
    // 初始化D矩阵为邻接矩阵
    for (v = 0; v < n; v++) {
        for (w = 0; w < n; w++) {
            D[v][w] = G[v][w];
        }
    }
    
    // Floyd算法核心部分
    for (k = 0; k < n; k++) {
        for (v = 0; v < n; v++) {
            for (w = 0; w < n; w++) {
                if (D[v][w] > D[v][k] + D[k][w]) {
                    D[v][w] = D[v][k] + D[k][w];
                }
            }
        }
    }
}

int main() {
    int n, m;
    int G[MAXVEX][MAXVEX];  // 邻接矩阵
    int D[MAXVEX][MAXVEX];  // 最短路径矩阵
    int i, j;
    
    // 输入顶点数
    scanf("%d", &n);
    
    // 输入邻接矩阵
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &G[i][j]);
        }
    }
    
    // 计算所有点对的最短路径
    ShortestPath_Floyd(n, G, D);
    
    // 输入查询数量
    scanf("%d", &m);
    
    // 处理每个查询
    int value[MAXVEX] = {0};
    for (i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        value[i] = D[u][v];
    }

    // 输出查询结果
    for (i = 0; i < m; i++) {
        if (value[i] != 0) {
            printf("%d\n", value[i]);
        }
    }
    
    return 0;
}