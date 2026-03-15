#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// 邻接表节点结构
typedef struct AdjListNode {
    int dest;            // 目标节点编号
    struct AdjListNode* next; // 指向下一个邻接节点
} AdjListNode;

// 邻接表结构
typedef struct AdjList {
    AdjListNode* head;   // 指向第一个邻接节点
} AdjList;

// 图结构
typedef struct Graph {
    int V;               // 顶点数
    AdjList* array;      // 邻接表数组
} Graph;

// 创建新的邻接表节点
AdjListNode* newAdjListNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// 创建图
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;

    // 创建邻接表数组
    graph->array = (AdjList*)malloc(V * sizeof(AdjList));

    // 初始化每个邻接表为空
    for (int i = 0; i < V; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

// 添加边
void addEdge(Graph* graph, int src, int dest) {
    // 添加从src到dest的边
    AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head; // 插入到链表头部
    graph->array[src].head = newNode;

    // 如果是无向图，还需要添加从dest到src的边
    // newNode = newAdjListNode(src);
    // newNode->next = graph->array[dest].head;
    // graph->array[dest].head = newNode;
}

/*
    核心思路：
        1. 创建一个访问标记数组，标记每个节点是否被访问过
        2. 创建一个栈用于DFS
        3. 将当前节点压入栈中
        4. 弹出栈顶节点，如果该节点未被访问，则处理它，并将邻接节点压入栈中
        5. 重复步骤4，直到栈为空
*/
void DFS(Graph* graph, int v) {
    // 创建一个访问标记数组
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));
    for (int i = 0; i < graph->V; ++i) {
        visited[i] = false;
    }

    // 创建一个栈用于DFS
    int* stack = (int*)malloc(graph->V * sizeof(int));
    int top = -1;

    // 将当前节点压入栈中
    stack[++top] = v;

    while (top != -1) {
        // 弹出栈顶节点
        v = stack[top--];

        // 如果该节点未被访问，则处理它
        if (!visited[v]) {
            printf("%d ", v);
            visited[v] = true;
        }

        // 将邻接节点压入栈中
        AdjListNode* pCrawl = graph->array[v].head;
        while (pCrawl != NULL) {
            if (!visited[pCrawl->dest]) {
                stack[++top] = pCrawl->dest;
            }
            pCrawl = pCrawl->next;
        }
    }

    free(visited);
    free(stack);
}

int main() {
    int V = 5; // 图的顶点数
    Graph* graph = createGraph(V);

    // 添加边
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 4, 1);

    printf("深度优先遍历（从顶点 2 开始）:\n");
    DFS(graph, 2);

    return 0;
}