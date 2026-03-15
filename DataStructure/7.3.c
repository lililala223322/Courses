#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义二叉树节点结构
typedef struct TreeNode {
    char data;               // 节点存储的字符数据
    struct TreeNode *left;   // 左子节点指针
    struct TreeNode *right;  // 右子节点指针
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
    核心思路：
    递归遍历，用代码保证函数输入参数的两个节点处于对称位置。
    若该两节点出现一个NULL一个非NULL，则返回false。
    函数总值为true并上左右节点的左子节点对称值和右对称值，即有一处不对称就会造成最终结果不对称。
*/
bool isSymmetric(TreeNode* left, TreeNode* right) {
    // 全空，对称
    if (left == NULL && right == NULL) {
        return true;
    }

    // 有一个为空，不对称
    if (left != NULL && right == NULL) {
        return false;
    } else if (left == NULL && right != NULL) {
        return false;
    }

    // 继续递归判断
    return true && isSymmetric(left->left, right->left) && isSymmetric(left->right, right->right);
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


    if (isSymmetric(root->left, root->right)) {
        printf("二叉树是对称的\n");
    } else {
        printf("二叉树不是对称的\n");
    }

    // 释放内存
    freeTree(root);

    return 0;
}