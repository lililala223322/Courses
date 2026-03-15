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
    int tag;
} LinkedQueue;

// 初始化链队
void initQueue(LinkedQueue* queue) {
    queue->front = queue->rear = NULL;
    queue->tag == 0;
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

    queue->tag++;

    return;
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

    queue->tag--;

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

void task(int a[], int n) {
    // odd和even分别为奇数和偶数队列
    LinkedQueue odd , even;
    initQueue(&odd);
    initQueue(&even);

    for (int i = 0; i < n; i++)
    {
        // 按奇偶性分别入队
        if (a[i] % 2) {
            enqueue(&odd, a[i]);
        } else {
            enqueue(&even, a[i]);
        }
    }

    // 先搬偶数
    for (int i = 0; even.tag > 0; i++)
    {
        dequeue(&even, &a[i]);
    }

    // 再搬奇数
    for (int i = 4; i < 8; i++)
    {
        dequeue(&odd, &a[i]);
    }

}

int main() {
    int a[] = {1,2,3,4,5,6,7,8};
    int num = 8;

    task(a, num);

    printf("a[]:");
    for (int i = 0; i < num; i++)
    {
        printf("%d ",a[i]);
    }
    

    return 0;
}