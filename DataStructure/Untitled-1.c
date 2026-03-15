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

// 前序遍历（根-左-右）
void preorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    printf("%c ", root->data);  // 访问根节点
    preorderTraversal(root->left);  // 遍历左子树
    preorderTraversal(root->right); // 遍历右子树
}

// 中序遍历（左-根-右）
void inorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);   // 遍历左子树
    printf("%c ", root->data);      // 访问根节点
    inorderTraversal(root->right);  // 遍历右子树
}

// 后序遍历（左-右-根）
void postorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);   // 遍历左子树
    postorderTraversal(root->right);  // 遍历右子树
    printf("%c ", root->data);       // 访问根节点
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
    //       A
    //      / \
    //     B   C
    //    / \
    //   D   E
    TreeNode* root = createNode('A');
    root->left = createNode('B');
    root->right = createNode('C');
    root->left->left = createNode('D');
    root->left->right = createNode('E');

    printf("前序遍历: ");
    preorderTraversal(root);
    printf("\n");

    printf("中序遍历: ");
    inorderTraversal(root);
    printf("\n");

    printf("后序遍历: ");
    postorderTraversal(root);
    printf("\n");

    // 释放内存
    freeTree(root);

    return 0;
}