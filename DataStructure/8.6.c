#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int flag; // 邻接点编号
    int data; // 权值
    struct Node* next; // 指向下一个邻接点
} Node;

typedef struct {
    int num; // 节点编号
    Node* first; // 指向第一个邻接点
    struct HeadNode* next; // 指向下一个节点
} HeadNode;

typedef struct {
    HeadNode* head; // 头指针
    int num; // 节点个数
    int edge; // 边个数
} Graph;

// 创建图
Graph* createGraph() {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->head = (HeadNode*)malloc(sizeof(HeadNode));
    g->head->num = 1;
    g->head->first = NULL;
    g->head->next = NULL;
    g->num = 1;
    g->edge = 0;
    return g;
}

// 插入节点
void insertNode(Graph* g, int num) {
    HeadNode* p = g->head;
    while (p->next!= NULL && p->num < num) {
        p = p->next;
    }
    if (p->num == num) {
        printf("节点已存在！\n");
        return;
    }
    HeadNode* q = (HeadNode*)malloc(sizeof(HeadNode));
    q->num = num;
    q->first = NULL;
    q->next = NULL;
    p->next = q;
    g->num++;
}

// 插入边
void insertEdge(Graph* g, int num, int flag, int data) {

    // 先找到节点
    HeadNode* p = g->head;
    while (p->next!= NULL && p->num < num) {
        p = p->next;
    }
    if (p->num!= num) {
        printf("节点%d不存在！\n", num);
        return;
    }

    // 再找到尾部
    Node* temp = p->first;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }

    // 插入边
    Node* q = (Node*)malloc(sizeof(Node));
    q->flag = flag;
    q->data = data;
    q->next = NULL;
    if (p->first == NULL) {
        p->first = q;
    } else {
        temp->next = q;
    }
    temp = q;
    g->edge++;
}

// 辅助函数：检查路径中是否包含某个节点
bool contains(int path[], int pathLength, int node) {
    for (int i = 0; i < pathLength; i++) {
        if (path[i] == node) {
            return true;
        }
    }
    return false;
}
 
// 递归DFS寻找最长路径
void dfs(HeadNode* currentNode, int path[], int pathLength, int* maxLength, int* endNode) {
    // 将当前节点加入路径
    path[pathLength] = currentNode->num;
    pathLength++;
    
    // 更新最大长度和终点
    if (pathLength > *maxLength) {
        *maxLength = pathLength;
        *endNode = currentNode->num;
    }
    
    // 遍历所有邻接节点
    Node* neighbor = currentNode->first;
    while (neighbor != NULL) {
        int nextNode = neighbor->flag;
        
        // 检查邻接节点是否已在路径中
        if (!contains(path, pathLength, nextNode)) {
            // 找到邻接节点对应的HeadNode
            HeadNode* nextHead = currentNode->next;
            while (nextHead != NULL && nextHead->num != nextNode) {
                nextHead = nextHead->next;
            }
            
            if (nextHead != NULL) {
                // 递归访问邻接节点
                dfs(nextHead, path, pathLength, maxLength, endNode);
            }
        }
        neighbor = neighbor->next;
    }
}
 
// 寻找最长简单路径
int findLongestSimplePath(Graph* g, int startNum) {
    // 找到起始节点
    HeadNode* startNode = g->head;
    while (startNode != NULL && startNode->num != startNum) {
        startNode = startNode->next;
    }
    
    if (startNode == NULL) {
        printf("起始节点%d不存在！\n", startNum);
        return -1;
    }
    
    int maxLength = 0;
    int endNode = -1;
    int path[100];
    
    dfs(startNode, path, 0, &maxLength, &endNode);
    
    if (maxLength == 0) {
        printf("没有找到从节点%d出发的路径！\n", startNum);
        return -1;
    }
    
    printf("最长简单路径长度: %d, 终点: %d\n", maxLength, endNode);
    return endNode;
}

int main()
{
    Graph* g = createGraph();
    
    insertNode(g, 2);
    insertNode(g, 3);
    insertNode(g, 4);
    insertNode(g, 5);

    insertEdge(g, 1, 2, 1);
    insertEdge(g, 1, 3, 1);
    insertEdge(g, 1, 4, 1);
    insertEdge(g, 1, 5, 1);
    insertEdge(g, 2, 3, 1);
    insertEdge(g, 2, 5, 1);
    insertEdge(g, 3, 2, 1);
    insertEdge(g, 3, 5, 1);
    insertEdge(g, 4, 1, 1);
    insertEdge(g, 4, 3, 1);
    insertEdge(g, 5, 2, 1);
    insertEdge(g, 5, 4, 1);

    findLongestSimplePath(g, 1);

}