#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/*
    核心思路：
    该算法通过遍历二叉排序树来查找第一个值大于k的结点：
    从根结点开始，若当前结点值大于k，则记录该结点为候选结果，并继续在左子树中查找；
    若当前结点值小于等于k，则继续在右子树中查找。
*/

TreeNode* findFirstGreater(TreeNode* root, int k) {
    TreeNode *result = NULL;
    TreeNode *current = root;
    
    while (current != NULL) {
        if (current->key > k) {
            // 找到大于k的结点，更新结果并尝试找更小的满足条件的结点
            result = current;
            current = current->left;
        } else {
            // 当前结点小于等于k，继续在右子树中查找
            current = current->right;
        }
    }
    
    return result;
}

// 创建新结点
TreeNode* createNode(int key) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

int main() {
    // 二叉排序树
    TreeNode* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->left = createNode(12);
    root->right->right = createNode(18);
    
    int k = 7;
    TreeNode* node = findFirstGreater(root, k);
    
    if (node != NULL) {
        printf("第一个值大于 %d 的结点是 %d\n", k, node->key);
    } else {
        printf("没有找到值大于 %d 的结点\n", k);
    }
    
    return 0;
}