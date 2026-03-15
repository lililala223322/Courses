#include <stdio.h>
#include <stdlib.h>

// 定义节点结构
typedef struct Node {
    int row, col, value;
    struct Node *right, *down;
} Node;

// 定义行头和列头节点结构
typedef struct {
    Node **rowHeads; // 行头指针数组
    Node **colHeads; // 列头指针数组
    int rows, cols, numNodes;
} CrossList;

// 创建新的节点
Node* createNode(int row, int col, int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->row = row;
    node->col = col;
    node->value = value;
    node->right = node->down = NULL;
    return node;
}

// 初始化十字链表
CrossList* initCrossList(int rows, int cols) {
    CrossList *list = (CrossList *)malloc(sizeof(CrossList));
    list->rows = rows;
    list->cols = cols;
    list->numNodes = 0;
    list->rowHeads = (Node **)calloc(rows, sizeof(Node *));
    list->colHeads = (Node **)calloc(cols, sizeof(Node *));
    return list;
}

// 插入节点到十字链表
void insertNode(CrossList *list, int row, int col, int value) {
    Node *node = createNode(row, col, value);
    
    // 插入行链表
    Node **rowPtr = &list->rowHeads[row - 1];
    while (*rowPtr && (*rowPtr)->col < col) {
        rowPtr = &(*rowPtr)->right;
    }
    node->right = *rowPtr;
    *rowPtr = node;

    // 插入列链表
    Node **colPtr = &list->colHeads[col - 1];
    while (*colPtr && (*colPtr)->row < row) {
        colPtr = &(*colPtr)->down;
    }
    node->down = *colPtr;
    *colPtr = node;

    list->numNodes++;
}

// 打印十字链表（输出非零元素）
void printCrossList(CrossList *list) {
    for (int i = 0; i < list->rows; i++) {
        Node *node = list->rowHeads[i];
        while (node) {
            printf("%d %d %d\n", node->row, node->col, node->value);
            node = node->right;
        }
    }
}

// 释放十字链表
void freeCrossList(CrossList *list) {
    for (int i = 0; i < list->rows; i++) {
        Node *node = list->rowHeads[i];
        while (node) {
            Node *temp = node;
            node = node->right;
            free(temp);
        }
    }
    free(list->rowHeads);
    free(list->colHeads);
    free(list);
}

// 合并两个十字链表
CrossList* MatrixAdd(CrossList *A, CrossList *B) {
    CrossList *C = initCrossList(A->rows, A->cols);

    // 遍历A并插入到C
    for (int i = 0; i < A->rows; i++) {
        Node *node = A->rowHeads[i];
        while (node) {
            insertNode(C, node->row, node->col, node->value);
            node = node->right;
        }
    }

    // 遍历B并插入到C，处理相加
    for (int i = 0; i < B->rows; i++) {
        Node *nodeB = B->rowHeads[i];
        while (nodeB) {
            Node *nodeC = NULL;
            Node **colPtr = &C->colHeads[nodeB->col - 1];
            while (*colPtr && (*colPtr)->row < nodeB->row) {
                colPtr = &(*colPtr)->down;
            }
            if (*colPtr && (*colPtr)->row == nodeB->row) {
                // 节点已存在，累加值
                (*colPtr)->value += nodeB->value;
                if ((*colPtr)->value == 0) { // 如果相加后为零，删除节点
                    // 从行链表中删除
                    Node **rowPtr = &C->rowHeads[nodeB->row - 1];
                    while (*rowPtr && (*rowPtr)->col < nodeB->col) {
                        rowPtr = &(*rowPtr)->right;
                    }
                    if (*rowPtr && (*rowPtr)->col == nodeB->col) {
                        *rowPtr = (*rowPtr)->right;
                    }

                    // 从列链表中删除
                    *colPtr = (*colPtr)->down;
                }
            } else {
                // 节点不存在，直接插入
                if (!*colPtr || (*colPtr)->row > nodeB->row) {
                    insertNode(C, nodeB->row, nodeB->col, nodeB->value);
                }
            }
            nodeB = nodeB->right;
        }
    }

    return C;
}

int main() {
    int m, n, t1, t2;
    scanf("%d %d %d %d", &m, &n, &t1, &t2);

    CrossList *A = initCrossList(m, n);
    CrossList *B = initCrossList(m, n);

    for (int i = 0; i < t1; i++) {
        int row, col, value;
        scanf("%d %d %d", &row, &col, &value);
        insertNode(A, row, col, value);
    }

    for (int i = 0; i < t2; i++) {
        int row, col, value;
        scanf("%d %d %d", &row, &col, &value);
        insertNode(B, row, col, value);
    }

    CrossList *C = MatrixAdd(A, B);
    printCrossList(C);

    // 释放内存
    freeCrossList(A);
    freeCrossList(B);
    freeCrossList(C);

    return 0;
}