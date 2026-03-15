#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NODES 10000

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct Result {
    int selected;    
    int not_selected; 
} Result;

TreeNode* createTree(int* values, int size) {
    if (size == 0) return NULL;
    
    TreeNode** nodes = (TreeNode**)malloc(size * sizeof(TreeNode*));
    for (int i = 0; i < size; i++) {
        if (values[i] != -1) {
            nodes[i] = (TreeNode*)malloc(sizeof(TreeNode));
            nodes[i]->val = values[i];
            nodes[i]->left = NULL;
            nodes[i]->right = NULL;
        } else {
            nodes[i] = NULL;
        }
    }
    
    for (int i = 0; i < size; i++) {
        if (nodes[i] != NULL) {
            int left_idx = 2 * i + 1;
            int right_idx = 2 * i + 2;
            
            if (left_idx < size) {
                nodes[i]->left = nodes[left_idx];
            }
            if (right_idx < size) {
                nodes[i]->right = nodes[right_idx];
            }
        }
    }
    
    TreeNode* root = nodes[0];
    free(nodes);
    return root;
}

Result dfs(TreeNode* root) {
    if (root == NULL) {
        Result res = {0, 0};
        return res;
    }
    
    Result left = dfs(root->left);
    Result right = dfs(root->right);
    
    Result res;
    // 选择当前节点：不能选择子节点，但可以选择子节点的子节点
    res.selected = root->val + left.not_selected + right.not_selected;
    
    // 不选择当前节点：可以选择子节点（取子节点的最大收益）
    res.not_selected = (left.selected > left.not_selected ? left.selected : left.not_selected) +
                      (right.selected > right.not_selected ? right.selected : right.not_selected);
    
    return res;
}

int rob(TreeNode* root) {
    Result res = dfs(root);
    return res.selected > res.not_selected ? res.selected : res.not_selected;
}

int main() {
    char input[100000];
    scanf("%s", input);
    
    // 解析输入
    int values[MAX_NODES];
    int count = 0;
    char* token = strtok(input, ",");
    
    while (token != NULL) {
        values[count++] = atoi(token);
        token = strtok(NULL, ",");
    }
    
    TreeNode* root = createTree(values, count);

    int result = rob(root);
    printf("%d\n", result);
    
    return 0;
}