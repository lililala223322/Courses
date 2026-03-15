#include <stdio.h>

typedef struct SqStack
{
    int data[100];
    int *top;
} SqStack;

void initStack(SqStack *stack)
{
    stack->top = stack->data - 1;
}

void printStack(SqStack *stack)
{
    printf("Stack: ");
    int *temp = stack->top;
    do
    {
        printf("%d ", *temp--);
    } while (temp >= stack->data);
    printf("\n");
}

void push(SqStack *stack, int data)
{
    (stack->top)++;
    *(stack->top) = data;
}

void pop(SqStack *stack, int *data)
{
    *data = *(stack->top--);
}

void transfer(int d, int r) {
    SqStack stack;
    initStack(&stack);

    // 按位入栈再出栈就好
    while ( d != 0 ) {
        push(&stack, d%r);
        d = d/r;
    }

    printStack(&stack);
}

int main()
{
    int d , r ;
    printf("数据 进制\n");
    scanf("%d %d",&d,&r);

    transfer(d,r);
}
