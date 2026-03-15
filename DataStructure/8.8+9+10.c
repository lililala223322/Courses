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
    记一维数组path记录路径，则函数findPath从start开始遍历路径，同时记录路径长度length
    若start=end切length>0，则说明找到了环，打印路径
    check函数用于检查path里有没有start，以保证路径为简单路径，如果不是则放弃当前这条路
    以上两个条件都不满足则说明这条路还能继续往下走，则设置path[length]为当前节点
    这种设定有一个特别的好处：多个findCircle函数操作的path实际上是同一个数组，
    但由于各自的length不同，它们不会相互干扰，即一个数组满足多条路径需求
    记录完当前节点后根据当前节点的边去递归调用findCircle遍历整张图即可找到所有环
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

void findCircle(Graph* g, int start, int end, int path[], int length, int n) {
    // 找到循环
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
        findCircle(g, temp->flag, end, path, length, n);
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
    insertEdge(g, 2, 3, 1);
    insertEdge(g, 3, 1, 1);
    insertEdge(g, 3, 4, 1);
    insertEdge(g, 4, 5, 1);
    insertEdge(g, 5, 1, 1);

    int path[5] = {0};
    findCircle(g, 1, 1, path, 0, 5);

}