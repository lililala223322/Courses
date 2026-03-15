#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5  // 定义循环队列的最大容量

typedef struct {
    int data[MAX_SIZE];
    int front;  // 队头指针
    int rear;   // 队尾指针
    int size;   // 当前队列中的元素个数
} CircularQueue;

// 初始化循环队列
void initQueue(CircularQueue* queue) {
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
}

// 判断队列是否为空
bool isEmpty(CircularQueue* queue) {
    return queue->size == 0;
}

// 判断队列是否已满
bool isFull(CircularQueue* queue) {
    return queue->size == MAX_SIZE;
}

// 入队操作
bool enqueue(CircularQueue* queue, int value) {
    if (isFull(queue)) {
        printf("Queue is full!\n");
        return false;
    }
    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % MAX_SIZE;  // 循环移动
    queue->size++;
    return true;
}

// 出队操作
bool dequeue(CircularQueue* queue, int* value) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return false;
    }
    *value = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAX_SIZE;  // 循环移动
    queue->size--;
    return true;
}

// 打印队列中的所有元素
void printQueue(CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue: ");
    for (int i = 0; i < queue->size; i++) {
        int index = (queue->front + i) % MAX_SIZE;
        printf("%d ", queue->data[index]);
    }
    printf("\n");
}

int main() {
    CircularQueue queue;
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