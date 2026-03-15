#include <stdio.h>
#include <stdlib.h>

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

void leafFromRight(TreeNode* root) {
    if (root == NULL) return;

    // 打印叶子节点
    if (root->left == NULL && root->right == NULL) {
        printf("%c ", root->data);
        return;
    }
    
    // 递归，先处理右子树
    leafFromRight(root->right);
    leafFromRight(root->left);
}

/*
    核心思路：先序遍历二叉树并打印叶子，先递归处理右侧即可从右向左打印叶子节点
    思路2：先序遍历二叉树，叶子入栈，则出栈即为从右向左
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

    leafFromRight(root);

    // 释放内存
    freeTree(root);

    return 0;
}