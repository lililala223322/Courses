#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 定义链串节点
typedef struct LinkNode {
    char data;
    struct LinkNode *next;
} LinkNode;

// 定义链串结构
typedef struct LinkString{
    LinkNode *head; // 指向链串的头节点
    int length;     // 链串的长度
} LinkString;

// 初始化链串
void InitString(LinkString *S) {
    S->head = (LinkNode *)malloc(sizeof(LinkNode)); // 创建哨兵节点
    S->head->next = NULL;
    S->length = 0;
}

// 生成一个值等于chars的串S。
void StrAssign(LinkString *S, const char *chars) {
    InitString(S); // 清空原有串
    LinkNode *tail = S->head; // 从哨兵节点开始
    for (int i = 0; chars[i] != '\0'; i++) {
        LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode));
        newNode->data = chars[i];
        newNode->next = NULL;
        tail->next = newNode; // 将新节点连接到链表末尾
        tail = newNode;
        S->length++;
    }
}

/*
    算法思路：
    S为母串，sub为子串
    1.首先记录sub的首字母为startChar，并用一个结点startNode来记录S中最新的startChar的位置
    2.从startNode开始用temp结点检测后续是否为sub子串
    3.用计数器记录当前检测字符数，若计数器等于sub的长度则将startNode的前结点和temp.next连接起来。
    4.若检测到不等，则寻找下一个startNode并重复2、3，直到找不到下一个startNode。
    ps. 为方便链接，startNode指向startChar的前置结点；
        同时因为寻找startNode的过程就已经检测过sub的第一个元素了，故sub_temp从sub的第二个字符起算
*/
void deleteSub(LinkString *S, LinkString *sub) {
    char startChar = sub->head->next->data;
    LinkNode *S_temp = S->head, *sub_temp = sub->head->next->next, *startNode;
    bool flag = false;

    while (S_temp != NULL)
    {
        // 初始化startNode
        while (1)
        {
            // 母串没有子串的头字符，删除完成。
            if (S_temp->next == NULL) {
                return;
            }
            // 寻找子串的头字符
            if (S_temp->next->data == startChar) {
                startNode = S_temp;
                break;
            }
            S_temp = S_temp->next;
        }

        // 开始检测
        S_temp = startNode->next->next;
        while (1) {
            // 如果检测相等，则两边一起推进，计数器++
            if (sub_temp != NULL && S_temp->data == sub_temp->data) {
                S_temp = S_temp->next;
                sub_temp = sub_temp->next;
            }
            else {
                if (sub_temp == NULL) {
                    flag = true;
                    // 特殊情况：子串在母串的开头
                    if (startNode == S->head) {
                        S->head->next = S_temp;
                        S_temp = startNode;
                    }
                    else if (S_temp == NULL) {
                        // 特殊情况：子串在母串的末尾
                        startNode->next = NULL;
                    }
                    else {
                        // 普通情况，直接连接
                        startNode->next = S_temp;
                        S_temp = startNode;
                    }
                }
                // 退出检测，寻找下一个startNode
                break;
            } 
        }

        // flag指示是否有删除子串的操作，S_temp的变化会不一样。
        if (!flag) {
            S_temp = startNode->next;
        }
        sub_temp = sub->head->next->next;
        flag = false;
    }
}

int main()
{
    // 初始化
    LinkString S1, S2;
    InitString(&S1);
    InitString(&S2);

    // 输入数据
    char str1[100] = {0}, str2[100] = {0};
    printf("母串：");
    scanf("%s", str1);
    printf("子串：");
    scanf("%s", str2);

    // 赋值
    StrAssign(&S1, str1);
    StrAssign(&S2, str2);

    deleteSub(&S1, &S2);

    // 输出结果
    printf("删除后的母串：");
    LinkNode *temp = S1.head->next;
    while (temp != NULL) {
        printf("%c", temp->data);
        temp = temp->next;
    }
    printf("\n");

    return 0;
}