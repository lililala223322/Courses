#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 400

// 定义二叉树节点结构
typedef struct TreeNode {
    char data;               // 节点存储的字符数据
    struct TreeNode *left;   // 左子节点指针
    struct TreeNode *right;  // 右子节点指针
    struct TreeNode *parent; // 父节点指针
} TreeNode;

// 创建新节点
TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

// 释放二叉树内存
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/*
    核心思路：先序遍历二叉树，找得谁就是谁。
    NULL节点不return，做特殊处理
*/
void findX(TreeNode* root, TreeNode** X, char x) {
    // 找到就返回
    if (root->data == x) {
        *X = root;
        return;
    }

    // 没找到就继续先序遍历，并用下方方式处理NULL
    if (root->left != NULL) {
        findX(root->left, X, x);
    }
    if (root->right != NULL) {
        findX(root->right, X, x);
    }
}

void printfSons(TreeNode* root) {
    // 先序遍历
    if (root == NULL) return;
    printf("%c ", root->data);
    printfSons(root->left);
    printfSons(root->right);
}

int main() {
    // 构建一个简单的二叉树
    //        A
    //      /   \
    //     B     C
    //    / \   / 
    //   D   E F   
    TreeNode* root = createNode('A');
    root->left = createNode('B');
    root->right = createNode('C');
    root->left->left = createNode('D');
    root->left->right = createNode('E');
    root->right->left = createNode('F');

    char x = 'C';
    TreeNode* X = NULL;
    findX(root, &X, x);
    if (X == NULL) {
        printf("没有找到%c\n", x);
    } else {
        printf("%c的子孙为：", x);
        printfSons(X);
    }

    // 释放内存
    freeTree(root);

    return 0;
}