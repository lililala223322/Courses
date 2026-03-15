#include <stdio.h>
#include <stdlib.h>

// 定义链栈的节点结构
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 定义链栈结构
typedef struct LinkStack {
    int count;
    Node* top;  // 栈顶指针
} LinkStack;

// 初始化链栈
void initStack(LinkStack* stack) {
    stack->top = NULL;  // 栈顶指针初始化为空
}

// 打印链栈
void printStack(LinkStack* stack) {
    if (stack->top == NULL) {
        printf("Stack is empty.\n");
        return;
    }
    Node* temp = stack->top;
    printf("Stack: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// 压栈
void push(LinkStack* stack, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // 动态分配新节点
    if (newNode == NULL) {
        printf("Memory allocation failed, cannot push %d.\n", data);
        return;
    }
    
    newNode->data = data;
    newNode->next = stack->top;  // 新节点的next指向当前的栈顶
    stack->top = newNode;        // 栈顶指针更新为新节点
    printStack(stack);
}

// 出栈
void pop(LinkStack* stack, int* data) {
    if (stack->top == NULL) {  // 栈为空
        printf("Stack is empty, cannot pop.\n");
        return;
    }
    Node* temp = stack->top;   // 暂存栈顶节点
    *data = temp->data;        // 取出栈顶数据
    stack->top = temp->next;   // 栈顶指针指向下一个节点
    free(temp);                // 释放栈顶节点
    printStack(stack);
}

// 释放链栈
void freeStack(LinkStack* stack) {
    while (stack->top != NULL) {
        pop(stack, NULL);  // 逐个出栈并释放节点
    }
}

int main() {
    LinkStack stack;  // 定义一个链栈
    initStack(&stack);  // 初始化链栈

    int operate;
    printf("Enter operation (1: push, 2: pop, 0: exit):\n");
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
            push(&stack, x);
        } else if (operate == 2) {  // 出栈
            int x;
            pop(&stack, &x);
            if (x != 0) {  // 如果出栈成功，打印出栈的元素
                printf("Popped number: %d\n", x);
            }
        } else {
            printf("Invalid operation, please enter 1, 2, or 0.\n");
        }
    }

    freeStack(&stack);  // 释放链栈
    return 0;
}