#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_TREE_HT 100

// 哈夫曼树节点结构
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

// 最小堆结构
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

// 创建新节点
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// 创建最小堆
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// 交换两个最小堆节点
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// 最小堆化
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// 检查堆大小是否为1
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// 提取最小节点
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// 插入节点到最小堆
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// 构建最小堆
void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// 打印数组
void printArr(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

// 判断是否是叶子节点
int isLeaf(struct MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

// 创建并构建最小堆
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// 构建哈夫曼树
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

// 存储哈夫曼编码
void storeCodes(struct MinHeapNode* root, int arr[], int top, char* huffmanCode[]) {
    if (root->left) {
        arr[top] = 0;
        storeCodes(root->left, arr, top + 1, huffmanCode);
    }
    if (root->right) {
        arr[top] = 1;
        storeCodes(root->right, arr, top + 1, huffmanCode);
    }
    if (isLeaf(root)) {
        huffmanCode[(unsigned char)root->data] = (char*)malloc((top + 1) * sizeof(char));
        for (int i = 0; i < top; i++) {
            huffmanCode[(unsigned char)root->data][i] = arr[i] + '0';
        }
        huffmanCode[(unsigned char)root->data][top] = '\0';
    }
}

// 生成哈夫曼编码
void HuffmanCodes(char data[], int freq[], int size, char* huffmanCode[]) {
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    storeCodes(root, arr, top, huffmanCode);
}

// 解码哈夫曼编码
void decodeHuffman(struct MinHeapNode* root, char* str) {
    struct MinHeapNode* curr = root;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        if (isLeaf(curr)) {
            printf("%c", curr->data);
            curr = root;
        }
    }
}

// 释放哈夫曼编码内存
void freeHuffmanCodes(char* huffmanCode[], int size) {
    for (int i = 0; i < size; i++) {
        if (huffmanCode[i] != NULL) {
            free(huffmanCode[i]);
            huffmanCode[i] = NULL;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    char data[n];
    int freq[n];
    for (int i = 0; i < n; i++) {
        scanf(" %c", &data[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &freq[i]);
    }

    char* huffmanCode[256] = {NULL}; // 假设ASCII字符集
    HuffmanCodes(data, freq, n, huffmanCode);

    char encodeStr[100];
    char decodeStr[100] = {0};
    scanf("%s", encodeStr);
    
    // 编码
    for (int i = 0; i < strlen(encodeStr); i++) {
        printf("%s", huffmanCode[(unsigned char)encodeStr[i]]);
        strcat(decodeStr, huffmanCode[(unsigned char)encodeStr[i]]);
    }
    printf("\n");
    
    // 重新构建哈夫曼树用于解码
    struct MinHeapNode* root = buildHuffmanTree(data, freq, n);
    
    decodeHuffman(root, decodeStr);
    printf("\n");

    // 释放内存
    freeHuffmanCodes(huffmanCode, 256);
    
    return 0;
}