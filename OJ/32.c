#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

/* 创建新节点 */
Node *new_node(int val)
{
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->next = NULL;
    return p;
}

/* 尾插法建表：按数组顺序生成链表 */
Node *create_list(int a[], int n)
{
    Node *head = NULL, *tail = NULL;
    for (int i = 0; i < n; ++i) {
        Node *p = new_node(a[i]);
        if (!head)                  /* 第一个节点 */
            head = tail = p;
        else {
            tail->next = p;         /* 接在尾部 */
            tail = p;
        }
    }
    return head;
}

/* 在指定位置 pos(0-based) 插入值 val；pos=0 表示最前 */
void insert(Node **head, int pos, int val)
{
    Node *p = new_node(val);
    if (pos == 0) {               /* 插在头部 */
        p->next = *head;
        *head = p;
        return;
    }
    /* 找到第 pos-1 个节点 */
    Node *cur = *head;
    for (int i = 0; cur && i < pos - 1; ++i) cur = cur->next;
    if (!cur) {                   /* pos 超出当前长度，直接尾插 */
        cur = *head;
        while (cur->next) cur = cur->next;
        cur->next = p;
    } else {                      /* 正常插入 */
        p->next = cur->next;
        cur->next = p;
    }
}

/* 遍历打印链表值，空格分隔 */
void print_list(Node *head)
{
    for (Node *p = head; p; p = p->next) {
        printf("%d", p->data);
        if (p->next) putchar(' ');
    }
    putchar('\n');
}

/* 测试用主函数 */
int main(void)
{
    int a[] = {10, 20, 30};
    Node *head = create_list(a, 3);   /* 当前链表：10 20 30 */
    print_list(head);

    insert(&head, 0, 5);   /* 插最前：5 10 20 30 */
    insert(&head, 2, 15);  /* 插位置2：5 10 15 20 30 */
    insert(&head, 10, 99); /* 超尾，尾插：5 10 15 20 30 99 */
    print_list(head);

    

    return 0;
}