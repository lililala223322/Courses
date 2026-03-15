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
    if (*head == NULL) {
        *head = newNode;
        newNode->prev = head;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// 就地删除双链表中所有重复节点
void deleteDuplicates(Node** head) {
    Node* current = *head;

    while (current != NULL && current->next != NULL) {
        if (current->data == current->next->data) {
            // 找到重复节点，删除当前节点的下一个节点
            Node* duplicate = current->next;
            current->next = duplicate->next;
            if (duplicate->next != NULL) {
                duplicate->next->prev = current;
            }
            free(duplicate);
        } else {
            // 移动到下一个不同的节点
            current = current->next;
        }
    }
}

// 打印双链表
void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

// 主函数
int main() {
    Node* head = NULL;

    // 构造双链表 1 <-> 2 <-> 2 <-> 2 <-> 3 <-> 5 <-> 5
    insertEnd(&head, 1);
    insertEnd(&head, 2);
    insertEnd(&head, 2);
    insertEnd(&head, 2);
    insertEnd(&head, 3);
    insertEnd(&head, 5);
    insertEnd(&head, 5);    

    printf("原双链表: ");
    printList(head);

    deleteDuplicates(&head);

    printf("删除重复节点后的双链表: ");
    printList(head);

    return 0;
}