#include <stdio.h>

typedef struct SqStack
{
    char data[100];
    char *top;
} SqStack;

void initStack(SqStack *stack)
{
    stack->top = stack->data - 1;
}

void printStack(SqStack *stack)
{
    char *temp = stack->top;
    do
    {
        printf("%c", *temp--);
    } while (temp >= stack->data);
}

void push(SqStack *stack, char data)
{
    (stack->top)++;
    *(stack->top) = data;
}

char pop(SqStack *stack)
{
    return *(stack->top--);
}

int main()
{
    char str[100];
    int numOfCircle;
    printf("循环长度:");
    scanf("%d",&numOfCircle);
    printf("循环字符串:");
    scanf("%s",str);

    SqStack stack;
    initStack(&stack);
    for (int i = 0; str[i] != 0 ; i++)
    {
        // 持续入栈
        push(&stack, str[i]);
        // 若指示器走到当前循环末尾，则打印当前栈并重置栈
        if ( !( (i+1) % numOfCircle) ) {
            printStack(&stack);
            stack.top = stack.data - 1;
        }
    }
    
}
