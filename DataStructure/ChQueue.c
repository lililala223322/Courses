#include <stdio.h>
#include <stdlib.h>

// 定义节点结构
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 定义链队结构
typedef struct LinkedQueue {
    Node* front;  // 队头指针
    Node* rear;   // 队尾指针
} LinkedQueue;

// 初始化链队
void initQueue(LinkedQueue* queue) {
    queue->front = queue->rear = NULL;
}

// 判断队列是否为空
int isEmpty(LinkedQueue* queue) {
    return queue->front == NULL;
}

// 入队操作
void enqueue(LinkedQueue* queue, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// 出队操作
int dequeue(LinkedQueue* queue, int* value) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return -1;  // 表示出队失败
    }

    Node* temp = queue->front;
    *value = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL) {  // 如果队列为空，更新rear指针
        queue->rear = NULL;
    }

    free(temp);
    return 0;  // 表示出队成功
}

// 打印队列中的所有元素
void printQueue(LinkedQueue* queue) {
    Node* current = queue->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 释放队列占用的内存
void freeQueue(LinkedQueue* queue) {
    Node* current = queue->front;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    queue->front = queue->rear = NULL;
}

int main() {
    LinkedQueue queue;
    initQueue(&queue);

    int operate;
    printf("Enter operation (1: enQueue, 2: deQueue, 0: exit):\n");
    while (1) {
        printf("Input operation: ");
        if (scanf("%d", &operate) != 1) {  // 读取用户操作
            printf("Invalid input, please enter a number.\n");
            // 清空输入缓冲区
            while (getchar() != '\n');
            continue;
        }
        if (operate == 0) {  // 退出
            printf("Exiting program.\n");
            break;
        } else if (operate == 1) {  // 压栈
            int x;
            printf("Enter a number to push: ");
            if (scanf("%d", &x) != 1) {  // 读取要压入栈的数字
                printf("Invalid input, please enter a number.\n");
                // 清空输入缓冲区
                while (getchar() != '\n');
                continue;
            }
            enqueue(&queue, x);
        } else if (operate == 2) {  // 出栈
            int x;
            dequeue(&queue, &x);
            if (x != 0) {  // 如果出栈成功，打印出栈的元素
                printf("Popped number: %d\n", x);
            }
        } else {
            printf("Invalid operation, please enter 1, 2, or 0.\n");
        }
        printf("Queue:");
        printQueue(&queue);
    }

    return 0;
}