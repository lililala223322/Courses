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
    先解释一下本算法的邻接表是什么：
    结构同ppt所讲，第一列是节点编号，每一行内的结点则是出边的方向，权值和下一个结点的指针。
    所以，要找i的入边邻接点需要遍历所有非i的行，去看谁的出边方向是i。
*/

void outEdge(Graph* g, int num) {
    HeadNode* p = g->head;
    for (int i = 1; i <= g->num; i++, p = p->next) {
        if (i == num) continue; // 跳过自己
        // 在行内挨个看
        for (Node* temp = p->first; temp != NULL; temp = temp->next) {
            if (temp->flag == num) {
                printf("节点%d的入边邻接点是%d，权值为%d\n", temp->flag, i, temp->data);
            }
        }
    }
}

int main()
{
    Graph* g = createGraph();
    
    insertNode(g, 2);
    insertNode(g, 3);
    insertNode(g, 4);
    insertNode(g, 5);

    insertEdge(g, 1, 2, 1);
    insertEdge(g, 1, 3, 2);
    insertEdge(g, 1, 5, 3);
    insertEdge(g, 2, 1, 3);
    insertEdge(g, 2, 5, 3);
    insertEdge(g, 3, 4, 4);
    insertEdge(g, 3, 1, 3);
    insertEdge(g, 3, 2, 3);
    insertEdge(g, 4, 2, 4);
    insertEdge(g, 4, 1, 3);
    insertEdge(g, 5, 3, 3);
    insertEdge(g, 5, 1, 4);

    outEdge(g, 1);

}