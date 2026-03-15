#include <stdio.h>
#include <stdlib.h>

// 哈希表节点结构
typedef struct HashNode {
    int key;
    struct HashNode *next;
} HashNode;

// 哈希表结构
typedef struct {
    int size;       // 哈希表大小
    HashNode **table; // 拉链法存储的数组
} HashTable;

// 创建哈希表
HashTable *createHashTable(int size) {
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    ht->size = size;
    ht->table = (HashNode **)malloc(size * sizeof(HashNode *));
    for (int i = 0; i < size; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

// 哈希函数（除留余数法）
int hash(int key, int size) {
    return key % size;
}

// 插入关键字到哈希表
void insert(HashTable *ht, int key) {
    int index = hash(key, ht->size);
    HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->next = ht->table[index]; // 头插法
    ht->table[index] = newNode;
}

/*
    核心思路：
    通过除留余数法计算哈希值定位链表头节点，再遍历链表查找目标关键字并删除：
    用 k % size 计算哈希值，确定链表头节点；
    遍历链表，找到 key == k 的节点；
    调整前驱节点的 next 指针以跳过目标节点。
*/

void Remove(HashTable *ht, int k) {
    int index = hash(k, ht->size);
    HashNode *prev = NULL;
    HashNode *curr = ht->table[index];

    // 遍历链表查找目标节点
    while (curr != NULL && curr->key != k) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Key %d not found in the hash table.\n", k);
        return;
    }

    // 删除节点
    if (prev == NULL) {
        ht->table[index] = curr->next; // 删除的是头节点
    } else {
        prev->next = curr->next;       // 删除的是中间或尾节点
    }
    printf("Key %d removed successfully.\n", k);
}

// 打印哈希表
void printHashTable(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        printf("Bucket %d: ", i);
        HashNode *curr = ht->table[i];
        while (curr != NULL) {
            printf("%d -> ", curr->key);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}

int main() {
    HashTable *ht = createHashTable(10);

    // 插入数据
    insert(ht, 7);
    insert(ht, 17);
    insert(ht, 27);
    insert(ht, 37);

    printf("Hash table before removal:\n");
    printHashTable(ht);

    // 删除关键字7
    Remove(ht, 7);

    printf("\nHash table after removal:\n");
    printHashTable(ht);

    return 0;
}