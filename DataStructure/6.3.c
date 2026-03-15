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

// 核心思路：
// 1.从0开始用start遍历S串
// 2.对于每次遍历，从start开始比对T串，如果失败则start指向下一个结点，然后再次比对
// 3.如果T串比对成功，则return值+1，start指向下一个结点，然后再次比对
int duplicateSubstrings(LinkString *S, LinkString *T, int start) {
    if (S->length - start <= T->length) {
        // 已经到达串尾
        return 0;
    }

    // 初始化头节点
    LinkNode *p = S->head;
    for (int i = 0; i < start; i++) {
        p = p->next;
    }

    // 遍历T串
    LinkNode *q = T->head;
    for (int i = 0; i < T->length; i++) { 
        if (p->data != q->data) {
            // 节点不匹配,检测下一节点
            return duplicateSubstrings(S, T, start + 1);
        }
        p = p->next;
        q = q->next;
    }

    return duplicateSubstrings(S, T, start + 1) + 1;
}

// 测试函数
int main() {
    LinkString S, T;
    InitString(&S);
    InitString(&T);
    StrAssign(&S, "aababad");
    StrAssign(&T, "aba");

    printf("T在S中出现了%d次\n", duplicateSubstrings(&S, &T, 0));

    return 0;
}