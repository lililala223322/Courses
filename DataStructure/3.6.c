#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 3

typedef struct circleQueue
{
    int data[MaxSize];
    int rear;
    int front;
    int tag;
}circleQueue;

void initQueue(circleQueue* queue)
{
    queue->front = 0;
    queue->rear = 0;
    queue->tag = 0;
}

// 此段代码否掉，因MaxSize已经确定，则可以用int型tag来确定空或满或常态。
/* 检查满没满
void isFull(circleQueue* queue)
{
    if ( (queue->front+1)%MaxSize == queue->rear ) {
        return true;
    }
    else {
        return false;
    }
}

// 检查空没空
bool isEmpty(circleQueue* queue)
{
    if ( queue->front == queue->rear) {
        return true;
    }
    else {
        return false;
    }
}
*/

// 入队，front前移
void enQueue(circleQueue* queue, int data)
{
    // 满了就退出
    if (queue->tag == MaxSize) {
        printf("队满\n");
        return;
    }

    // 赋值
    queue->data[(queue->front)++] = data;
    // 循环
    queue->front %= MaxSize; 
    queue->tag++;
}

void deQueue(circleQueue* queue, int* data)
{
    // 空了也退出
    if (queue->tag == 0) {
        printf("队空\n");
        return;
    }

    // 取值
    *data = queue->data[(queue->rear)++];
    // 循环
    queue->rear %= MaxSize;
    queue->tag--;
}

// 打印队列
void printQueue(circleQueue* queue)
{
    for (int i = 0; i < queue->tag; i++)
    {
        // 打印数据，data下标为front+计数器对长度取余
        printf("%d ",queue->data[(queue->rear + i) % MaxSize]);
    }
    printf("\n");
    return;
}

int main()
{
    circleQueue queue;
    initQueue(&queue);

    int operate;
    printf("输入操作 (1: 入队, 2: 出队, 0: 退出):\n");
    while (1) {
        printf("输入操作: ");
        scanf("%d", &operate);

        if (operate == 0) {  // 退出
            printf("退出.\n");
            break;

        } else if (operate == 1) {  // 入队
            int x;
            printf("入队数据: ");
            scanf("%d", &x);
            enQueue(&queue, x);

        } else if (operate == 2) {  // 出队
            int x;
            deQueue(&queue, &x);
            if (x != 0) {  // 如果出队成功，打印出队的元素
                printf("出队数据: %d\n", x);
            }

        } else {
            printf("操作数不合法\n");
        }

        printf("队列:");
        printQueue(&queue);
        printf("\n");
    }
}

