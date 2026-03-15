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

// 在串S的第pos个字符之前插入串T。
bool StrInsert(LinkString *S, int pos, const LinkString *T) {
    if (pos < 1 || pos > S->length + 1) return FALSE;

    LinkNode *p = S->head;
    for (int i = 1; i < pos - 1 && p != NULL; i++) {
        p = p->next;
    }

    LinkNode *tHead = T->head;
    if (pos == 1) { // 插入到头部
        while (tHead != NULL) {
            LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode));
            newNode->data = tHead->data;
            newNode->next = S->head;
            S->head = newNode;
            tHead = tHead->next;
            S->length++;
        }
    } else { // 插入到中间或尾部
        LinkNode *prev = p;
        while (tHead != NULL) {
            LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode));
            newNode->data = tHead->data;
            newNode->next = prev->next;
            prev->next = newNode;
            prev = newNode;
            tHead = tHead->next;
            S->length++;
        }
    }
    return TRUE;
}

// 从串S中删除第pos个字符起长度为len的子串。
bool StrDelete(LinkString *S, int pos, int len) {
    if (pos < 1 || pos > S->length || len < 0 || pos + len - 1 > S->length) return FALSE;

    LinkNode *p = S->head;
    LinkNode *prev = NULL;
    for (int i = 1; i < pos && p != NULL; i++) {
        prev = p;
        p = p->next;
    }

    for (int i = 0; i < len && p != NULL; i++) {
        LinkNode *temp = p;
        p = p->next;
        free(temp);
        S->length--;
    }

    if (prev != NULL) {
        prev->next = p;
    } else {
        S->head = p; // 删除从头开始的部分
    }

    return TRUE;
}

// 由串T复制得串S。
void StrCopy(LinkString *S, const LinkString *T) {
    StrAssign(S, ""); // 清空S
    LinkNode *current = T->head;
    while (current != NULL) {
        StrInsert(S, S->length + 1, &(LinkString){.head = (LinkNode[]){{current->data, NULL}}, .length = 1});
        current = current->next;
    }
}

// 若S>T,则返回值大于0;如S=T,则返回值0;若S<T,则返回值小于0。
int StrCompare(const LinkString *S, const LinkString *T) {
    LinkNode *p = S->head;
    LinkNode *q = T->head;
    while (p != NULL && q != NULL) {
        if (p->data != q->data) return p->data - q->data;
        p = p->next;
        q = q->next;
    }
    return S->length - T->length;
}

// 将S清为空串。
void StrClear(LinkString *S) {
    LinkNode *current = S->head;
    while (current != NULL) {
        LinkNode *temp = current;
        current = current->next;
        free(temp);
    }
    S->head = NULL;
    S->length = 0;
}

// 将串T的值连接在串S的后面。
bool StrCat(LinkString *S, const LinkString *T) {
    LinkNode *tail = S->head;
    if (tail == NULL) {
        StrCopy(S, T);
        return TRUE;
    }
    while (tail->next != NULL) {
        tail = tail->next;
    }
    LinkNode *current = T->head;
    while (current != NULL) {
        LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode));
        newNode->data = current->data;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
        current = current->next;
        S->length++;
    }
    return TRUE;
}

// 用Sub返回串S的第pos个字符起长度为len的子串。
bool SubString(LinkString *Sub, const LinkString *S, int pos, int len) {
    if (pos < 1 || pos > S->length || len < 0 || pos + len - 1 > S->length) return FALSE;

    InitString(Sub);
    LinkNode *p = S->head;
    for (int i = 1; i < pos && p != NULL; i++) {
        p = p->next;
    }

    // 由于上面循环逻辑复杂且存在错误，以下是最终正确且简化的SubString实现
    LinkNode *startNode = S->head;
    for (int i = 1; i < pos && startNode != NULL; i++) {
        startNode = startNode->next;
    }
    LinkNode **subTail = &Sub->head;
    for (int i = 0; i < len && startNode != NULL; i++) {
        *subTail = (LinkNode *)malloc(sizeof(LinkNode));
        (*subTail)->data = startNode->data;
        (*subTail)->next = NULL;
        subTail = &(*subTail)->next;
        startNode = startNode->next;
        Sub->length++;
    }
    return TRUE;
}

// 释放链串内存
void FreeString(LinkString *S) {
    StrClear(S);
}

// 测试函数
int main() {
    LinkString S, T, Sub;
    InitString(&S);
    InitString(&T);
    StrAssign(&S, "Hello");
    StrAssign(&T, " World");
    StrCat(&S, &T);
    printf("Concatenated: ");
    LinkNode *current = S.head;
    while (current != NULL) {
        printf("%c", current->data);
        current = current->next;
    }
    printf("\n");

    SubString(&Sub, &S, 7, 5);
    printf("Substring: ");
    current = Sub.head;
    while (current != NULL) {
        printf("%c", current->data);
        current = current->next;
    }
    printf("\n");

    StrInsert(&S, 6, &Sub);
    printf("After Insert: ");
    current = S.head;
    while (current != NULL) {
        printf("%c", current->data);
        current = current->next;
    }
    printf("\n");

    StrDelete(&S, 6, 5);
    printf("After Delete: ");
    current = S.head;
    while (current != NULL) {
        printf("%c", current->data);
        current = current->next;
    }
    printf("\n");

    LinkString Copy;
    InitString(&Copy);
    StrCopy(&Copy, &S);
    printf("Copied: ");
    current = Copy.head;
    while (current != NULL) {
        printf("%c", current->data);
        current = current->next;
    }
    printf("\n");
    printf("Compare (S, T): %d\n", StrCompare(&S, &T));

    // 释放内存
    FreeString(&S);
    FreeString(&T);
    FreeString(&Sub);
    FreeString(&Copy);

    return 0;
}