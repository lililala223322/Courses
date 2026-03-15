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
    核心思路：
    先序遍历二叉树，但带上一个int参数layer，每次递归时+1则可表示当前节点所在层数
    所以，当节点不不为空时节点数++，遍历二叉树即可统计每一层的节点数。
    从存储每一层节点的数组取最大值即为二叉树的宽度。
*/
void countOfLayer(TreeNode* root, int num[], int layer) {
    if (root == NULL) return;

    // 非空则当前层节点+1，并继续统计子节点
    num[layer]++;
    countOfLayer(root->left, num, layer+1);
    countOfLayer(root->right, num, layer+1);
}

int main() {
    // 构建一个简单的二叉树
    //        A
    //      /   \
    //     B     C
    //    / \   / \
    //   D   E F   G 
    TreeNode* root = createNode('A');
    root->left = createNode('B');
    root->right = createNode('C');
    root->left->left = createNode('D');
    root->left->right = createNode('E');
    root->right->left = createNode('F');

    int num[MAXSIZE] = {0}; // 每层节点个数，下标即个数
    countOfLayer(root, num, 0); // 统计每个字符出现的次数

    int max_width = 0; // 二叉树宽度
    for (int i = 0; i < MAXSIZE; i++) {
        max_width = max_width > num[i]? max_width : num[i]; // 取最大值
    }

    printf("二叉树宽度为：%d\n", max_width);

    // 释放内存
    freeTree(root);

    return 0;
}