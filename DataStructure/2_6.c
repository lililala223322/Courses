#include <stdio.h>
#include <stdlib.h>

// 定义双链表节点结构
typedef struct Node {
    int data;
    struct Node* prev;
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
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    int numberOfPoint = 0;

    if (*head == NULL) {
        *head = newNode;
        newNode->prev = NULL;
        newNode->next = *head;
    } else {
        Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
            numberOfPoint++;
        }
        
        // 特殊处理，记第三个节点的prev为NULL
        if (numberOfPoint+2 == 3) {
            temp->next = newNode;
            newNode->next = *head;
            newNode->prev = NULL;
        }
        else {
        temp->next = newNode;
        newNode->next = *head;
        newNode->prev = temp;
        }
    }
}

// 寻找问题节点并修复
void priorMender (Node** head)
{
    // 令current和prev并向前推进
    Node* current = *head;
    current = current->next;
    Node* prevNode = *head;

    // 从头遍历链表
    while (current != *head) {
        // 若current的prev==NULL，则令current的prev=prevNode以修复。
        if (current->prev == NULL) {
            current->prev = prevNode;
        }
        else {
            current = current->next;
            prevNode = prevNode->next;
        }
    }
}

// 打印双链表
void printList(Node* head) {
    Node* node = head;
    while(node->next != head) {
        node = node->next;
    }

    while(node != NULL) {
        printf("%d ",node->data);
        node = node->prev;
    }
    printf("\n");
}

// 主函数
int main() {
    Node* head = NULL;

    // 构造双链表
    insertEnd(&head, 1);
    insertEnd(&head, 2);
    insertEnd(&head, 3);
    insertEnd(&head, 4);
    insertEnd(&head, 5);
    insertEnd(&head, 6);
    insertEnd(&head, 7);    

    printf("修复前的双链表: ");
    printList(head);

    priorMender(&head);

    printf("用反向打印来检测: ");
    printList(head);

    return 0;
}