#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0

// 定义链串节点
typedef struct LinkNode {
    char data;
    struct LinkNode *next;
} LinkNode;

// 定义链串结构
typedef struct {
    LinkNode *head; // 指向链串的头节点
    int length;     // 链串的长度
} LinkString;

// 初始化链串
void InitString(LinkString *S) {
    S->head = NULL;
    S->length = 0;
}

// 生成一个值等于chars的串S。
void StrAssign(LinkString *S, const char *chars) {
    InitString(S); // 清空原有串
    LinkNode *tail = NULL;
    for (int i = 0; chars[i] != '\0'; i++) {
        LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode));
        newNode->data = chars[i];
        newNode->next = NULL;
        if (S->head == NULL) {
            S->head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
        S->length++;
    }
}

/*
    算法思路：
    1.判断x@x是否是奇数长度，如果是偶数长度，直接false。
    2.遍历S，为X赋值。
    4.判断X的长度是否等于S的长度的一半，如果不相同，直接false。
    5.遍历S，判断x@x。
*/

bool is_XatX(LinkString *S)
{
    // x@x一定是奇数长度
    if (S->length%2 == 0) {
        return false;
    }

    LinkString X;
    InitString(&X);
    LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode));
    newNode->data = S->head->data;
    newNode->next = NULL;
    X.head = newNode;
    X.length = 1;

    LinkNode *S_temp = S->head->next;
    // 为X赋值
    while (S_temp->data != '@' )
    {
        LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode));
        newNode->data = S_temp->data;
        newNode->next = NULL;
        
        LinkNode *X_temp = X.head;
        while (X_temp->next != NULL) {
            X_temp = X_temp->next;
        }
        X_temp->next = newNode;
        X.length++;
        if (S_temp->next == NULL) {
            return false;
        }
        S_temp = S_temp->next;
    }

    // 前后两个X长度不相同，直接false
    if (X.length != S->length/2) {
        return false;
    }

    // 遍历S，判断x@x
    LinkNode *X_temp = X.head;
    S_temp = S_temp->next; // 跳过@
    while (S_temp != NULL) {
        if (S_temp->data != X_temp->data) {
            return false;
        }
        S_temp = S_temp->next;
        X_temp = X_temp->next;
    }

    return true;
}

// 测试函数
int main() {
    // 初始化
    LinkString S;
    InitString(&S);

    // 输入数据
    char str[100] = {0};
    printf("串：");
    scanf("%s", str);

    // 赋值
    StrAssign(&S, str);
    
    if (is_XatX(&S)) {
        printf("是");
    }
    else {
        printf("不是");
    }
}