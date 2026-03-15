#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTEX 100
#define INFINITY 10000

void Dijkstra(int graph[MAX_VERTEX][MAX_VERTEX], int n, int start, int end) {
    int dist[MAX_VERTEX];       // 存储起点到各点的最短距离
    int visited[MAX_VERTEX] = {0}; // 标记顶点是否已访问
    int prev[MAX_VERTEX];       // 存储前驱顶点，用于回溯路径
    
    // 初始化
    for (int i = 0; i < n; i++) {
        dist[i] = graph[start][i];
        prev[i] = (graph[start][i] != INFINITY) ? start : -1;
    }
    
    visited[start] = 1;
    dist[start] = 0;
    
    // 主循环，每次找出一个顶点的最短路径
    for (int i = 1; i < n; i++) {
        int min_dist = INFINITY;
        int current = -1;
        
        // 找出未访问顶点中距离最小的
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                current = j;
            }
        }
        
        if (current == -1) break; // 没有可达顶点
        
        visited[current] = 1;
        
        // 更新邻接顶点距离
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[current][j] != INFINITY) {
                if (dist[current] + graph[current][j] < dist[j]) {
                    dist[j] = dist[current] + graph[current][j];
                    prev[j] = current;
                }
            }
        }
    }
    
    // 回溯路径
    int path[MAX_VERTEX];
    int path_length = 0;
    int temp = end;
    
    while (temp != start && temp != -1) {
        path[path_length++] = temp;
        temp = prev[temp];
    }
    
    if (temp == -1) {
        printf("No path exists from %d to %d\n", start, end);
        return;
    }
    
    path[path_length++] = start;
    
    // 反向输出路径
    for (int i = path_length - 1; i >= 0; i--) {
        printf("%d\n", path[i]);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    int graph[MAX_VERTEX][MAX_VERTEX];
    
    // 输入邻接矩阵
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    int start, end;
    scanf("%d %d", &start, &end);
    
    Dijkstra(graph, n, start, end);
    
    return 0;
}
