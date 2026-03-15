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
 
// 删除链表中第一个出现的某个值
int deleteNode(Node** head, int key) {
    Node* temp = *head;
    Node* prev = NULL;
 
    // 如果头节点就是要删除的节点
    if (temp != NULL && temp->data == key) {
        *head = temp->next;
        free(temp);
        return 1;
    }
 
    // 搜索要删除的节点
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }
 
    // 如果没有找到该值
    if (temp == NULL) {
        printf("没有找到值为 %d 的节点\n", key);
        return 0;
    }
 
    // 从链表中删除节点
    prev->next = temp->next;
    free(temp);
}
 
// 打印链表
void printList(Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}
 
// 主函数
int main() {
    Node* head = NULL;
 
    insertEnd(&head, 1);
    insertEnd(&head, 2);
    insertEnd(&head, 2);
    insertEnd(&head, 3);
    insertEnd(&head, 1);
 
    printf("链表内容: ");
    printList(head);
 
    while (deleteNode(&head, 2));
    printf("删除2后链表内容: ");
    printList(head);
 
    return 0;
}
