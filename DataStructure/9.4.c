#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int key;
    struct TreeNode *left, *right;
} TreeNode;

// 递归查找并记录路径
TreeNode* findPathHelper(TreeNode* root, int k, TreeNode** path, int* index) {
    if (root == NULL) return NULL;
    
    path[(*index)++] = root; // 记录当前结点到路径
    
    if (root->key == k) return root;
    if (k < root->key) return findPathHelper(root->left, k, path, index);
    else return findPathHelper(root->right, k, path, index);
}

/*
    核心思路：
    利用二叉排序树的性质，从根结点开始，根据目标关键字k与当前结点的比较结果，
    选择左或右子树递归查找，同时记录遍历的结点形成路径。
    若找到k，则返回路径；否则路径终止于空结点。
*/

TreeNode** findPath(TreeNode* root, int k, int* pathLen) {
    TreeNode** path = (TreeNode**)malloc(100 * sizeof(TreeNode*)); // 假设路径长度不超过100
    *pathLen = 0;
    TreeNode* result = findPathHelper(root, k, path, pathLen);
    
    if (result == NULL) {
        free(path);
        return NULL; // 未找到，释放内存
    }
    return path; // 返回路径数组
}

// 打印路径
void printPath(TreeNode** path, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", path[i]->key);
    }
    printf("\n");
}

int main() {
    // 构建示例BST
    TreeNode n3 = {3, NULL, NULL};
    TreeNode n5 = {5, NULL, NULL};
    TreeNode n2 = {2, NULL, NULL};
    TreeNode n4 = {4, &n2, &n5};
    TreeNode n1 = {1, &n3, &n4};
    TreeNode* root = &n1;

    int pathLen;
    TreeNode** path = findPath(root, 5, &pathLen);
    if (path) {
        printf("查找路径: ");
        printPath(path, pathLen); // 输出：1 4 5
        free(path);
    } else {
        printf("未找到关键字\n");
    }
    return 0;
}