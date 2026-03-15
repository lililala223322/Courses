#include <stdio.h>
#include <stdlib.h>

typedef int Element;

// 定义双链表节点结构，用于存储大数的每一位
typedef struct NodeList {
    Element value;
    struct NodeList *next;
    struct NodeList *prev;
} *Node;

// 初始化链表，使其成为一个空的循环链表
void initializeList(Node head) {
    if (!head) return;
    head->value = 0;  // 初始化为0
    head->prev = head->next = head;  // 形成循环链表
}

// 在链表尾部插入新节点
void appendNode(Node head, Element value) {
    if (!head) return;

    Node newNode = (Node)malloc(sizeof(struct NodeList));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    
    newNode->value = value;
    newNode->prev = head->prev;
    newNode->next = head;
    head->prev->next = newNode;
    head->prev = newNode;
}

// 释放链表所有节点的内存
void freeList(Node head) {
    if (!head) return;

    Node current = head->next;
    Node temp;
    while (current != head) {
        temp = current;
        current = current->next;
        free(temp);
    }
    // 重新将链表初始化为空循环链表
    head->next = head->prev = head;
}

// 大数乘以整数
void multiply(Node head, int factor) {
    if (!head || factor == 0) return;

    Node current = head->prev;  // 从链表尾部开始
    int carry = 0;
    while (current != head) {
        carry += current->value * factor;
        current->value = carry % 10;  // 保留个位
        carry /= 10;  // 进位
        current = current->prev;
    }
}

// 大数除以整数
void divide(Node head, int divisor) {
    if (!head || divisor == 0) return;

    Node current = head->next;  // 从链表头部开始
    int remainder = 0, temp; // 初始化余数为0
    while (current != head) {
        temp = remainder * 10 + current->value; // temp是上一位的余数与本位数据的合
        remainder = temp % divisor; // 再次计算余数
        current->value = temp / divisor;
        current = current->next;
    }
}

// 使用PPT里的公式计算PI值
void computePI(Node head, int terms) {
    if (!head || terms <= 0) return;

    for (int k = terms; k > 0; --k) {
        divide(head, 2 * k + 1);  // 除以奇数
        multiply(head, k);       // 乘以当前项系数
        head->next->value += 2;  // 累加2到链表第一个有效节点
    }
}

// 输出PI值
void printPI(Node head, int precision) {
    if (!head || precision < 0) return;

    Node current = head->next;  // 从链表第一个有效节点开始
    if (current == head) return;

    printf("%d.", current->value);  // 输出整数部分
    current = current->next;
    
    while (current != head && precision > 0) {
        printf("%d", current->value);
        current = current->next;
        precision--;
    }
}

int main() {
    struct NodeList PI_head;
    initializeList(&PI_head);

    int precision;
    scanf("%d", &precision);

    // 初始化链表，设置精度
    for (int i = 0; i < precision + 6; ++i) {
        appendNode(&PI_head, 0);
    }
    PI_head.next->value = 1;  // 链表第一个有效节点设为1

    // 根据精度计算所需的项数
    int terms = precision * 4 + 50;  // 经验公式
    computePI(&PI_head, terms);

    // 输出PI值
    printPI(&PI_head, precision);

    // 释放链表内存
    freeList(&PI_head);
    return 0;
}