#include <stdio.h>
#include <limits.h>

#define MAX_N 100
#define INF 10000

int n;
int graph[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];
int next_node[MAX_N][MAX_N]; // 用于重建路径

void floydWarshall() {
    // 初始化距离矩阵和路径矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != INF && i != j) {
                next_node[i][j] = j; // 如果i和j之间有直接边，则j是i的下一个节点
            } else {
                next_node[i][j] = -1; // 否则设为-1
            }
        }
    }

    // Floyd-Warshall算法核心部分
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && 
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next_node[i][j] = next_node[i][k]; // 更新路径
                }
            }
        }
    }
}

void printPath(int i, int j) {
    if (next_node[i][j] == -1) {
        return; // 没有路径
    }
    printf("%d\n", i); // 打印当前节点
    while (i != j) {
        i = next_node[i][j]; // 移动到下一个节点
        printf("%d\n", i);
    }
}

int main() {
    // 输入图的节点数
    scanf("%d", &n);
    
    // 输入邻接矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    // 初始化next_node矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            next_node[i][j] = -1;
        }
    }
    
    floydWarshall();
    
    int m;

    scanf("%d", &m);


    int path[m][2];
    // 输入路径


    for (int k = 0; k < m; k++) {
        scanf("%d %d", &path[k][0], &path[k][1]);
    }

    // 输出路径
    for (int k = 0; k < m; k++) {
        printPath(path[k][0], path[k][1]);
    }
    
    return 0;
}