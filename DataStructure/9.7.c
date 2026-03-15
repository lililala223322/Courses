#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/*
    核心思路：
    通过遍历二叉排序树来查找关键字为k的结点的前驱结点，
    从根结点开始，若当前结点值等于k，则检查其左子树是否存在，
    若存在则前驱为左子树的最右结点；
    若当前结点值大于k，则继续在左子树中查找；
    若当前结点值小于k，则将当前结点设为前驱候选并继续在右子树中查找，
    最终返回找到的前驱结点或NULL。
*/

TreeNode* findPredecessor(TreeNode* root, int k) {
    TreeNode *pre = NULL;
    TreeNode *current = root;
    
    while (current != NULL) {
        if (current->key == k) {
            // 找到目标结点，pre即为其前驱
            if (current->left != NULL) {
                // 如果目标结点有左子树，前驱是其左子树的最右结点
                TreeNode *temp = current->left;
                while (temp->right != NULL) {
                    temp = temp->right;
                }
                pre = temp;
            }
            return pre;
        } else if (k < current->key) {
            current = current->left;
        } else {
            pre = current; // 更新前驱候选
            current = current->right;
        }
    }
    
    return NULL; // 未找到关键字为k的结点（根据题目假设，此情况不会发生）
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
    TreeNode* pre = findPredecessor(root, k);
    
    if (pre != NULL) {
        printf("关键字 %d 的前驱结点是 %d\n", k, pre->key);
    } else {
        printf("关键字 %d 没有前驱结点\n", k);
    }
    
    return 0;
}