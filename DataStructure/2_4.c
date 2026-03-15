#include <stdio.h>
#include <stdlib.h>

typedef struct  Node
{
    int data;
    struct Node* next;
} Node;

// 创建一个新节点
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 插入一个节点到链表的末尾
void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
 
// 查询链表中是否存在某个值
int search(Node* head, int key) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == key) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}
 
// 打印链表
void printList(Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// 求差集
void difference(Node* head_A, Node* head_B, Node** head_C)
{

    while (head_A != NULL) {
        // 查找B中是否有当前的A值，无则插入
        if (!search(head_B, head_A->data)) {
            insertEnd(head_C, head_A->data);
        }
        head_A = head_A->next;
    }
}

// 主函数
int main() {
    Node* head_A = NULL;
    Node* head_B = NULL;

    insertEnd(&head_A, 1);
    insertEnd(&head_A, 3);
    insertEnd(&head_A, 2);

    insertEnd(&head_B, 5);
    insertEnd(&head_B, 1);
    insertEnd(&head_B, 4);
    insertEnd(&head_B, 2);

    printf("链表A: ");
    printList(head_A);
    printf("链表B: ");
    printList(head_B);

    Node* head_C = NULL;
    difference(head_A, head_B, &head_C);
    printf("链表C: ");
    printList(head_C);
    
 
    return 0;
}
