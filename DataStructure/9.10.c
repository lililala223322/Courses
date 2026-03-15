#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10 // 哈希表大小

// 哈希表节点
typedef struct HashNode {
    int key;
    int value;
    struct HashNode *next;
} HashNode;

// 哈希表结构
typedef struct {
    HashNode *table[TABLE_SIZE];
    int size; // 当前元素数量
} HashTable;

// 初始化哈希表
void initHashTable(HashTable *ht) {
    ht->size = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

// 哈希函数（除留余数法）
int hash(int key) {
    return key % TABLE_SIZE;
}

// 插入键值对
void insert(HashTable *ht, int key, int value) {
    int index = hash(key);
    HashNode *node = (HashNode *)malloc(sizeof(HashNode));
    node->key = key;
    node->value = value;
    node->next = ht->table[index];
    ht->table[index] = node;
    ht->size++;
}

/*
    核心思路：
    遍历哈希表中所有非空链表，对每个键值对执行一次查找操作，记录查找次数。
    累加所有键值对的查找次数，除以总键值对数量，得到平均值。
*/

int search(HashTable *ht, int key, int *value) {
    int index = hash(key);
    HashNode *node = ht->table[index];
    int count = 0;
    while (node != NULL) {
        count++;
        if (node->key == key) {
            *value = node->value;
            return count; // 返回查找次数
        }
        node = node->next;
    }
    return 0; // 未找到
}

// 计算成功情况下的平均查找长度
float ASL1(HashTable *ht) {
    if (ht->size == 0) return 0.0f;
    
    float total = 0.0f;
    int found = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        HashNode *node = ht->table[i];
        while (node != NULL) {
            int dummy;
            total += search(ht, node->key, &dummy); // 查找当前节点，累加查找次数
            found++;
            node = node->next;
        }
    }
    return total / found; // 平均查找长度
}

int main() {
    HashTable ht;
    initHashTable(&ht);
    
    // 插入示例数据
    insert(&ht, 1, 10);
    insert(&ht, 11, 20); // 与1冲突
    insert(&ht, 21, 30); // 与1冲突
    insert(&ht, 2, 40);
    
    printf("ASL1 (成功情况下的平均查找长度): %.2f\n", ASL1(&ht));
    return 0;
}