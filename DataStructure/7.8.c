#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 400

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
    把二叉树按层次遍历填入数组后，数组中间没有空位即为完全二叉树。
    用num记录当前节点在数组中的位置，若节点不存在则填入-1。
    先序遍历，故遍历左子树时计数x2+1，右子树时计数x2+2。
    又可知，因为没有对最后一个节点做判断，故产生的数组里，最后一个节点背后还会有一些没有意义的-1。
    故此处设计函数complement解决该问题。
    经以上处理，我们可以得到下标+1即为节点编号的二叉树数组，且中间的空位为-1，未使用的位置为空。
    故只要该数组没有-1则为完全二叉树。
*/
void isComplete(TreeNode* root, char binaryTree[], int num) {
    // 节点赋值
    binaryTree[num] = root->data;

    // 递归处理左右子树
    if (root->left != NULL) {
        isComplete(root->left, binaryTree, num*2+1);
    } else {
        binaryTree[num*2+1] = -1;
    }

    if (root->right != NULL) {
        isComplete(root->right, binaryTree, num*2+2);
    } else {
        binaryTree[num*2+2] = -1;
    }
}

void complement(char binaryTree[]) {
    // 找到最后一个有效节点的下标
    int count = 0;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (binaryTree[i] != 0 && binaryTree[i] != -1) {
            count = i;
        }
    }

    // 填充剩余位置为0
    for (int i = count+1; i < MAX_SIZE; i++) {
        binaryTree[i] = 0;
    }
}

int main() {
    // 构建一个简单的二叉树
    //        A
    //      /   \
    //     B     C
    //    / \     \
    //   D   E     G
    TreeNode* root = createNode('A');
    root->left = createNode('B');
    root->right = createNode('C');
    root->left->left = createNode('D');
    root->left->right = createNode('E');
    root->right->right = createNode('G');

    char binaryTree[MAX_SIZE] = {0};
    isComplete(root, binaryTree, 0);
    complement(binaryTree);

    printf("二叉树的层次遍历序列为：");
    for (int i = 0; i < MAX_SIZE; i++) {
        if (binaryTree[i] == -1) {
            printf("# ");
        } else if (binaryTree[i] != 0) {
            printf("%c ", binaryTree[i]);
        }
    }

    bool isCompleteTree = true;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (binaryTree[i] == -1) {
            isCompleteTree = false;  
        }
    }
    
    if (isCompleteTree) {
        printf("\n该二叉树是完全二叉树");
    } else {
        printf("\n该二叉树不是完全二叉树");
    }
    

    // 释放内存
    freeTree(root);

    return 0;
}