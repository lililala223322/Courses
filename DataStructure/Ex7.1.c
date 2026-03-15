#include <stdio.h>
#include <limits.h>

#define MAX_N 100
#define INF 10000

int n;
int graph[MAX_N][MAX_N];
int dist[MAX_N];
int visited[MAX_N];

void dijkstra(int start) {
    // 初始化距离数组
    for (int i = 0; i < n; i++) {
        dist[i] = graph[start][i];
        visited[i] = 0;
    }
    
    // 起始点已访问
    visited[start] = 1;
    dist[start] = 0;
    
    for (int i = 1; i < n; i++) {
        // 找到当前未访问节点中距离最小的节点
        int min_dist = INF;
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        
        if (u == -1) break; // 所有可达节点都已处理
        
        visited[u] = 1;
        
        // 更新通过u节点到达其他节点的距离
        for (int v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] != INF && 
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

int main() {
    // 读取输入
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    
    // 初始化距离数组
    dijkstra(0);
    
    // 输出结果
    for (int i = 0; i < n; i++) {
        printf("%d\n", dist[i]);
    }
    
    return 0;
}