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
void insertEdge(Graph* g, int num, int flag, int data, int flag2) {
    // 因为图无向，所以插入两次
    if (flag2) {
        insertEdge(g, flag, num, data, 0);
    }

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
    令一维数组Node[num]，其中num为节点个数，该数组下标为节点编号，初值为1，表示该节点未访问。
    前提条件：本表是伪无向表，插入i，j的时候会同步插入权值相同的j，i。
    本算法尝试根据Node数组遍历结点的边：
    若Node[i]为1，表示该结点为访问过，开始遍历；若为0说明是某个分量的一部分，跳过。
    而对于i的每条边，将对应的终点也置为0，表示这些边和i是连通的，是同一个分量。
    如果i的边连向了已经置0的结点，说明i是上一个连通分量的一部分，count不变，i++，调用下一次函数。
    若遍历持续到了边为NULL，说明这是一个新分量，count++，i++，调用下一次函数
    重复上述过程，直到Node全0。
    则，在这个过程中，每次调用该函数都会覆盖掉至少一个结点，直到所有分量都被遍历完。
*/

// i为遍历计数器，num为节点个数，count为连通分量个数
int countConnectedComponent(Graph* g, int node[],int i ,int num, int count) {
    // 遍历完毕
    if (i >= num) {
        return count;
    }
    
    // 结点i已熄灭
    if (node[i] == 0) {
        return countConnectedComponent(g, node, i + 1, num, count);
    }

    // 先找结点i
    HeadNode* p = g->head;
    for (int j = 0; j < i; j++) {
        p = p->next;
    }
    Node* temp = p->first;
    // 遍历结点i的边
    while (temp != NULL) {
        if ( node[temp->flag -1] == 0 ) {
        // 这个结点和上个连通分量是一起的，不找了，直接下一个
        return countConnectedComponent(g, node, i + 1, num, count);
        } else {
            // 这个结点和上个连通分量不是一起的，标记一下
            node[temp->flag -1] = 0;
            temp = temp->next;
        }
        
    }
    // 遍历完毕，该结点已访问
    node[i] = 0;
    return countConnectedComponent(g, node, i + 1, num, count + 1);
}

int main()
{
    Graph* g = createGraph();
    
    insertNode(g, 2);
    insertNode(g, 3);
    insertNode(g, 4);
    insertNode(g, 5);

    // 1→2→3→1 4→5，共2个分量
    insertEdge(g, 1, 2, 1, 1);
    insertEdge(g, 2, 3, 1, 1);
    insertEdge(g, 3, 1, 1, 1);
    insertEdge(g, 4, 5, 1, 1);

    int num = g->num;
    int node[num];
    for (int i = 0; i < num; i++) {
        node[i] = 1;
    }

    printf("这张图有%d个连通分量\n", countConnectedComponent(g, node, 0, num, 0));

}