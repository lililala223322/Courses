#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTEX_NUM 100  // 最大顶点数
#define INFINITY INT_MAX    // 表示无穷大

// 邻接矩阵表示的图结构
typedef struct {
    int vertex[MAX_VERTEX_NUM];          // 顶点数组
    int edges[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  // 邻接矩阵
    int vexnum, arcnum;                  // 图的当前顶点数和边数
} MGraph;

// 初始化图
void InitGraph(MGraph *G) {
    // 内置图数据
    G->vexnum = 5;
    G->arcnum = 8;
    
    // 初始化顶点数组（这里简单使用顶点编号）
    for (int i = 0; i < G->vexnum; i++) {
        G->vertex[i] = i;
    }
    
    // 初始化邻接矩阵
    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {
            if (i == j) {
                G->edges[i][j] = 0;  // 顶点到自身的距离为0
            } else {
                G->edges[i][j] = INFINITY;  // 初始化为无穷大
            }
        }
    }
    
    // 内置边信息
    int edge_info[8][3] = {
        {0, 1, 2}, {0, 3, 4}, {0, 4, 1},
        {1, 2, 3}, {1, 3, 6}, {1, 4, 5},
        {2, 4, 7}, {3, 4, 2}
    };
    
    for (int k = 0; k < G->arcnum; k++) {
        int v1 = edge_info[k][0];
        int v2 = edge_info[k][1];
        int weight = edge_info[k][2];
        G->edges[v1][v2] = weight;
        G->edges[v2][v1] = weight;  // 无向图，双向设置
    }
}

// 狄克斯特拉算法求最短路径长度
void Dijkstra(MGraph G, int s, int t) {
    int dist[MAX_VERTEX_NUM];    // 存储从s到各顶点的最短距离
    bool visited[MAX_VERTEX_NUM]; // 标记顶点是否已找到最短路径
    
    // 初始化距离数组和访问标记数组
    for (int i = 0; i < G.vexnum; i++) {
        dist[i] = G.edges[s][i];
        visited[i] = false;
    }
    
    dist[s] = 0;       // 顶点到自身的距离为0
    visited[s] = true; // 起点s已访问
    
    // 遍历所有顶点
    for (int i = 1; i < G.vexnum; i++) {
        // 找到当前未访问顶点中距离最小的顶点u
        int u = -1;
        int min_dist = INFINITY;
        for (int j = 0; j < G.vexnum; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }
        
        // 如果找不到更小的距离或已找到目标顶点t，则退出
        if (u == -1 || u == t) {
            break;
        }
        
        visited[u] = true;  // 标记顶点u已访问
        
        // 更新顶点u的所有邻接顶点v的距离
        for (int v = 0; v < G.vexnum; v++) {
            if (!visited[v] && G.edges[u][v] != INFINITY && 
                dist[u] + G.edges[u][v] < dist[v]) {
                dist[v] = dist[u] + G.edges[u][v];
            }
        }
    }
    
    // 输出结果
    if (dist[t] == INFINITY) {
        printf("顶点%d到顶点%d没有路径\n", s, t);
    } else {
        printf("顶点%d到顶点%d的最短路径长度为: %d\n", s, t, dist[t]);
    }
}

int main() {
    MGraph G;
    InitGraph(&G);
    
    // 内置起点和终点
    int s = 0;
    int t = 2;
    
    if (s < 0 || s >= G.vexnum || t < 0 || t >= G.vexnum) {
        printf("顶点编号无效!\n");
        return 0;
    }
    
    Dijkstra(G, s, t);
    
    return 0;
}