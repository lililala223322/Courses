#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

/* 反转链表，返回新头指针 */
ListNode *reverseList(ListNode *head) {
    ListNode *prev = NULL, *curr = head;
    while (curr) {
        ListNode *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

int main(void) {
    char ch;
    int v;
    ListNode *head = NULL, *tail = NULL;

    /* 读入 '[' */
    if (scanf(" %c", &ch) != 1 || ch != '[') {
        /* 格式非法，按空处理 */
        putchar('\n');
        return 0;
    }

    /* 读数字直到遇到 ']' */
    while (scanf(" %d", &v) == 1) {
        ListNode *node = (ListNode *)malloc(sizeof(ListNode));
        node->val  = v;
        node->next = NULL;
        if (!head) head = tail = node;
        else { tail->next = node; tail = node; }
        /* 看下一个字符是不是 ']' */
        scanf(" %c", &ch);
        if (ch == ']') break;
        /* 把非']'的字符退回，继续读数字 */
        ungetc(ch, stdin);
    }

    /* 反转链表 */
    head = reverseList(head);

    /* 输出结果 */
    if (!head) {
        putchar('\n');
    } else {
        ListNode *p = head;
        printf("%d", p->val);
        while ((p = p->next) != NULL) printf(" %d", p->val);
        putchar('\n');
    }

    /* 释放内存 */
    while (head) {
        ListNode *tmp = head;
        head = head->next;
        free(tmp);
    }
    return 0;
}