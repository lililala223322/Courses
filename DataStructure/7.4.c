#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

/*
    核心思路：
    先序遍历二叉树，为每个节点填充其父节点指针。
*/
void fillParent(TreeNode* root) {
    if (root == NULL) return;

    // 填充左节点
    if (root->left!= NULL) {
        root->left->parent = root;
        fillParent(root->left);
    }

    // 填充右节点
    if (root->right!= NULL) {
        root->right->parent = root;
        fillParent(root->right);
    }
}

void printParent(TreeNode* root) {
    if (root->parent == NULL) {
        printf("%c没有父节点\n", root->data);
    } else {
        printf("%c的父节点是%c\n", root->data, root->parent->data);
    }

    if (root->left != NULL) {
        printParent(root->left);
    }

    if (root->right != NULL) {
        printParent(root->right);
    }
}

// 释放二叉树内存
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
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

    fillParent(root);
    printParent(root);

    // 释放内存
    freeTree(root);

    return 0;
}