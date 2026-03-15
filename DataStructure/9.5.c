#include <stdio.h>
#include <stdlib.h>

// 结点结构
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

/*
    核心思路：
    该算法的核心思路是利用二叉排序树的中序遍历性质。
    中序遍历BST会按升序访问所有结点，因此在遍历过程中只需收集前m个访问的结点即可。
    这里我们通过递归式中序遍历BST，并用一个计数器跟踪已收集的结点数，当计数器达到m时提前终止遍历。
*/

// 中序遍历并收集前m小的结点
void inorderTraversal(TreeNode* root, int* result, int* count, int m) {
    if (root == NULL || *count >= m) {
        return;
    }
    // 遍历左子树
    inorderTraversal(root->left, result, count, m);
    // 访问当前结点
    if (*count < m) {
        result[(*count)++] = root->val;
    }
    // 遍历右子树
    inorderTraversal(root->right, result, count, m);
}

// 输出前m小的结点
void printFirstMSmallest(TreeNode* root, int m) {
    if (root == NULL || m <= 0) {
        return;
    }
    int* result = (int*)malloc(m * sizeof(int));
    int count = 0;
    inorderTraversal(root, result, &count, m);
    // 输出结果
    for (int i = 0; i < count; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    free(result);
}

// 创建新结点
TreeNode* createNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int main() {
    // 示例
    TreeNode* root = createNode(5);
    root->left = createNode(3);
    root->right = createNode(7);
    root->left->left = createNode(2);
    root->left->right = createNode(4);
    root->right->left = createNode(6);
    root->right->right = createNode(8);

    int m = 4;
    printf("前%d小的结点: ", m);
    printFirstMSmallest(root, m); // 输出: 2 3 4 5

    // 释放内存（实际使用时需要实现完整的树销毁函数）
    return 0;
}