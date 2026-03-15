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
    printf("push:%d\n",data);
    printStack(stack);
}

void pop(SqStack *stack, int *data)
{
    *data = *(stack->top--);
    printf("pop:%d\n",*data);
    printStack(stack);
}

int main()
{
    SqStack stack;
    initStack(&stack);

    int operate;
    scanf("%d",&operate);
    while (operate)
    {
        if (operate == 1)
        {
            int x = 0;
            scanf("%d", &x);
            push(&stack, x);
        }

        else if (operate == 2)
        {
            int x = 0;
            pop(&stack, &x);
        }

        else
        {
            printf("?\n");
        }

        scanf("%d",&operate);
    }
}
