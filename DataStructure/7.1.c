#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构
typedef struct TreeNode {
    char data;               // 节点存储的字符数据
    struct TreeNode *left;   // 左子节点指针
    struct TreeNode *right;  // 右子节点指针
} TreeNode;

typedef struct Tree {
    TreeNode* root;  // 根节点指针
    int n;           // 节点个数
} Tree;

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
    return newNode;
}

// 统计叶子节点个数
int countLeafNodes(TreeNode* root) {
    if (root == NULL) {
        return 0;  // 空节点不是叶子节点
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;  // 当前节点是叶子节点
    }
    // 递归计算左右子树的叶子节点个数
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// 统计总节点数
int countTotalNodes(TreeNode* root) {
    if (root == NULL) {
        return 0;  // 空节点不计数
    }
    // 递归计算左右子树的节点个数，并加上当前节点
    return 1 + countTotalNodes(root->left) + countTotalNodes(root->right);
}

// 释放二叉树内存
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/*
    核心思路：易知n1 = n - 2*n0 + 1，故统计叶子和总结点数即可。
*/

int main() {
    // 构建一个简单的二叉树
    //       A
    //      / \
    //     B   C
    //    / \   \
    //   D   E   F
    TreeNode* root = createNode('A');
    root->left = createNode('B');
    root->right = createNode('C');
    root->left->left = createNode('D');
    root->left->right = createNode('E');
    root->right->right = createNode('F');

    int n = countTotalNodes(root);
    int n0 = countLeafNodes(root);
    printf("n1节点个数: %d\n", n - 2*n0 + 1);

    // 释放内存
    freeTree(root);

    return 0;
}