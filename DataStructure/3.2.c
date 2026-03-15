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
        printf("栈空.\n");
        return;
    }
    Node* temp = stack->top;
    printf("栈: ");
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
        printf("栈满，%d无法入栈.\n", data);
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
        printf("栈空\n");
        return;
    }
    Node* temp = stack->top;   // 暂存栈顶节点
    *data = temp->data;        // 取出栈顶数据
    stack->top = temp->next;   // 栈顶指针指向下一个节点
    free(temp);                // 释放栈顶节点
    printStack(stack);
}

void specPop(LinkStack* stack, int num, int* data) {
    Node* temp = stack->top;

    // 正常出栈
    if (num == 1)
    {
        pop(stack, data);
        return;
    }

    // 寻找对应结点
    for (int i = 2; i < num; i++)
    {
        temp = temp->next;
        if (temp == NULL) {
            printf("结点 %d 不存在",num);
            return;
        }
    }
    Node* specNode = temp->next;

    // specNode出栈，temp连接下一个点
    *data = specNode->data;
    temp->next = specNode->next;
    printStack(stack);
}

// 释放链栈
void freeStack(LinkStack* stack) {
    while (stack->top != NULL) {
        specPop(stack, 1, NULL);  // 逐个出栈并释放节点
    }
}

int main() {
    LinkStack stack;  // 定义一个链栈
    initStack(&stack);  // 初始化链栈

    int operate;
    printf("输入操作 (1: 入栈, 2: 出栈, 0: 退出):\n");
    while (1) {
        printf("输入操作: ");
        scanf("%d", &operate);

        if (operate == 0) {  // 退出
            printf("退出.\n");
            break;
        } else if (operate == 1) {  // 压栈
            int x;
            printf("入栈数据: ");
            scanf("%d", &x);
            push(&stack, x);
        } else if (operate == 2) {  // 出栈
            int x , n;
            printf("出栈位置: ");
            scanf("%d", &n);
            specPop(&stack, n, &x);
            printf("出栈数据: %d\n", x);
        } else {
            printf("操作数不合法\n");
        }
    }

    freeStack(&stack);  // 释放链栈
    return 0;
}