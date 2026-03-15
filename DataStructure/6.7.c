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

// 核心思路：maxNode返回当前节点与后续链表中更大的一方，minNode同理
int maxNode(Node* p) {
    if (p != NULL)
        return p->data > maxNode(p->next)? p->data : maxNode(p->next);
}

int minNode(Node* p) {
    if (p != NULL)
        return p->data < minNode(p->next)? p->data : minNode(p->next);
}

int main() {
    Node* head = NULL;
    insert(&head, 0);
    insert(&head, 1);
    insert(&head, 2);
    insert(&head, 3);
    insert(&head, 4);
    insert(&head, 5);
    insert(&head, 6);
    insert(&head, 7);


    printf("最大值为%d\n", maxNode(head));
    printf("最小值为%d\n", minNode(head));

    return 0;

}