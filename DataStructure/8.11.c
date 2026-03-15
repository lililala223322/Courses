#include <stdio.h>
#include <stdlib.h>

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

/*
    核心思路：
    把上一张图的函数稍微改改就行了，
    在向下深度搜索的时候，flag=k就跳过
    
*/

// 检查有没有重复
int check(int path[], int start, int n) {
    for (int i = 0; i < n; i++)
    {
        if (path[i] == start)
        {
            return 1;   
        }
    }
    return 0;
}

void findPath(Graph* g, int start, int end, int k, int path[], int length, int n) {
    // 找到目标
    if (start == end && length) {
        for (int i = 0; i < length; i++)
        {
            printf("%d->", path[i]);
        }
        printf("%d\n", end);
    }

    // 非简单路径
    if ( length && check(path, start, n) ) {
        return;
    }

    path[length++] = start;

    // 都不是，就找到当前start点，遍历其边
    HeadNode* p = g->head;
    while (p->next != NULL && p->num < start) {
        p = p->next;
    }
    if (p->num != start) {
        return;
    }

    Node* temp = p->first;
    while (temp != NULL) {
        if (temp->flag != k){
            findPath(g, temp->flag, end, k, path, length, n);
        }
        temp = temp->next;
    }
}

int main()
{
    Graph* g = createGraph();
    
    {
    insertNode(g, 2);
    insertNode(g, 3);
    insertNode(g, 4);
    insertNode(g, 5);
    }

    // 1→2→3→1 1→2→3→4→5→1，共2个环
    insertEdge(g, 1, 2, 1);
    insertEdge(g, 1, 3, 1);
    insertEdge(g, 1, 4, 1);
    insertEdge(g, 2, 5, 1);
    insertEdge(g, 3, 5, 1);
    insertEdge(g, 4, 5, 1);

    int path[5] = {0};
    // 找1到5的路径，但跳过2
    findPath(g, 1, 5, 2, path, 0, 5);

}