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

int min(int a, int b) {
    return a < b? a : b;
}

/*
    核心思路：带着层数进行先序遍历，找到即返回层数，这样可以避免继续遍历后续层次
    对于找到的这一群层次，用min函数求出最小值，即为所求值所在的最小层次。
*/
int findLowestX(TreeNode* root, char x, int layer) {
    if (root == NULL) {
        return INT_MAX;
    } else if (root->data == x) {
        return layer;
    }

    // 递归查找左右子树，用min求最小层次
    return min(findLowestX(root->left, x, layer + 1), findLowestX(root->right, x, layer + 1));
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
    //   D   C F   
    TreeNode* root = createNode('A');
    root->left = createNode('B');
    root->right = createNode('C');
    root->left->left = createNode('D');
    root->left->right = createNode('C');
    root->right->left = createNode('F');

    printf("'C'的最低层次为: %d\n", findLowestX(root, 'C', 0));

    // 释放内存
    freeTree(root);

    return 0;
}