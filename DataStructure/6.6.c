#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 创建新节点
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 尾插法
void insert(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next!= NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// 核心思路：因为找的是第一个匹配的结点，所以从表头开始找，找到即返回就行。
// 递归：代替循环
int getNo(Node* p, int x, int i) {
    if (p == NULL) {
        // 没找到
        return -1;
    } else if (p->data == x) {
        // 找到了
        return i;
    } else {
        // 还在找
        return getNo(p->next, x, i + 1);
    }

}

int main() {
    Node* head = NULL;
    insert(&head, 0);
    insert(&head, 1);
    insert(&head, 2);
    insert(&head, 3);
    insert(&head, 4);
    insert(&head, 3);
    insert(&head, 5);
    insert(&head, 7);


    printf("第一个值为3的结点序号为%d\n", getNo(head, 3, 0));

    return 0;

}

