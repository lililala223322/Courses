#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/*
    核心思路：
    该算法通过递归遍历二叉排序树来查找关键字为k的结点的层次：
    从根结点开始，初始层次设为1，若当前结点值等于k，则返回当前层次；
    若k小于当前结点值，则在左子树中继续查找，层次加1；
    若k大于当前结点值，则在右子树中继续查找，层次加1。
*/

int findLevel(TreeNode* root, int k, int level) {
    if (root == NULL) {
        return 0; // 未找到关键字为k的结点
    }
    
    if (root->key == k) {
        return level; // 找到目标结点，返回当前层次
    } else if (k < root->key) {
        return findLevel(root->left, k, level + 1); // 在左子树中继续查找，层次+1
    } else {
        return findLevel(root->right, k, level + 1); // 在右子树中继续查找，层次+1
    }
}

// 创建新结点
TreeNode* createNode(int key) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int main() {
    // 示例二叉排序树
    TreeNode* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->left = createNode(12);
    root->right->right = createNode(18);
    
    int k = 7;
    int level = findLevel(root, k, 1); // 从根结点开始，初始层次为1
    
    if (level != 0) {
        printf("关键字 %d 的结点层次为 %d\n", k, level);
    } else {
        printf("未找到关键字为 %d 的结点\n", k);
    }
    
    return 0;
}