#include <stdio.h>
#include <stdbool.h>

typedef struct SqStack
{
    char data[100];
    char *top;
} SqStack;

void initStack(SqStack *stack)
{
    stack->top = stack->data - 1;
}

void push(SqStack *stack, char data)
{
    (stack->top)++;
    *(stack->top) = data;
}

void pop(SqStack *stack, char *data)
{
    *data = *(stack->top--);
}

bool check_ante(char str[]) {
    // 初始化
    SqStack stack;
    initStack(&stack);
    int numOfSequence = 0; //用于检查两个序列是否等长的计数器

    // 序列1入栈    
    int i = 0;
    while (str[i] != '@') {
        push(&stack, str[i++]);
        numOfSequence++;
    }

    // 序列1出栈并与序列2对比
    char x;
    while (str[++i] != 0 ) {
        pop(&stack, &x);
        if (x != str[i]) {
            return false;
        }
        numOfSequence--;
    }

    // 计数器不为0则两个序列不等长
    if (!numOfSequence) {
        return true;
    }
    else {
        return false;
    }
}

int main()
{
    // 读取字符串
    char str[100] = {0};
    scanf("%s",str);

    if ( check_ante(str) ) {
        printf("对称");
    }
    else {
        printf("不对称");
    }

    return 0;
}
