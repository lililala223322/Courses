#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/*
    核心思路：因为这是一颗整数二叉排序树，所以按照中序遍历的逆序输出即可。
    先遍历右子树，再输出当前节点，最后遍历左子树。
*/
void printDescending(TreeNode *root) {
    if (root == NULL) return;
    printDescending(root->right); // 先遍历右子树
    printf("%d ", root->key);     // 输出当前节点
    printDescending(root->left);  // 最后遍历左子树
}

// 创建节点
TreeNode* createNode(int key) {
    TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

int main() {
    // 构建示例BST（手动创建）
    TreeNode *root = createNode(4);
    root->left = createNode(2);
    root->right = createNode(6);
    root->left->left = createNode(1);
    root->left->right = createNode(3);
    root->right->left = createNode(5);
    root->right->right = createNode(7);

    printf("递减输出: ");
    printDescending(root); // 输出: 7 6 5 4 3 2 1
    return 0;
}