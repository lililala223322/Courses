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

// 核心思路：递归思路同题目8，但是删除后不再直接退出
// pre用于记录前一个节点，方便删除
// 头节点为特殊情况，故单独处理
void delxAll(Node* p, Node* pre, int x) {

    if ( p == NULL ) {
        return;
    }

    // 头节点就是要找的值
    if (pre == NULL && p->data == x) {
        p = p->next;
        delxAll(p, NULL, x);
    }

    // 递归
    if (p->data == x) {
        // 正常删除
        pre->next = p->next;
        delxAll(pre->next, pre, x);
    } else {
        // 继续找
        delxAll(p->next, p, x);
    }

}

void printList(Node* head) {
    Node* temp = head;
    while (temp!= NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    insert(&head, 0);
    insert(&head, 1);
    insert(&head, 2);
    insert(&head, 3);
    insert(&head, 4);
    insert(&head, 3);
    insert(&head, 2);
    insert(&head, 3);
    int x = 3;

    printf("删除之前：");
    printList(head);
    delxAll(head, NULL, x);
    printf("删除%d之后：", x);
    printList(head);

    return 0;

}

