#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100000

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

long long minCost(int *basket1, int basket1Size, int *basket2, int basket2Size) {
    int freq[100001] = {0}; // 假设食品成本不超过 100000
    int min_val = 100001;

    // 统计频率并找最小值
    for (int i = 0; i < basket1Size; i++) {
        freq[basket1[i]]++;
        if (basket1[i] < min_val) min_val = basket1[i];
    }
    for (int i = 0; i < basket2Size; i++) {
        freq[basket2[i]]++;
        if (basket2[i] < min_val) min_val = basket2[i];
    }

    // 检查可行性
    for (int i = 1; i <= 100000; i++) {
        if (freq[i] % 2 != 0) return -1;
    }

    // 找出需要交换的食品
    int swap1[MAX_N], swap2[MAX_N];
    int idx1 = 0, idx2 = 0;

    // 重新统计每个篮子的频率
    int freq1[100001] = {0}, freq2[100001] = {0};
    for (int i = 0; i < basket1Size; i++) freq1[basket1[i]]++;
    for (int i = 0; i < basket2Size; i++) freq2[basket2[i]]++;

    for (int i = 1; i <= 100000; i++) {
        int total = freq1[i] + freq2[i];
        int target = total / 2;
        if (freq1[i] > target) {
            int extra = freq1[i] - target;
            for (int j = 0; j < extra; j++) swap1[idx1++] = i;
        } else if (freq2[i] > target) {
            int extra = freq2[i] - target;
            for (int j = 0; j < extra; j++) swap2[idx2++] = i;
        }
    }

    // 排序
    qsort(swap1, idx1, sizeof(int), cmp);
    qsort(swap2, idx2, sizeof(int), cmp);

    long long total_cost = 0;
    for (int i = 0; i < idx1; i++) {
        int direct_cost = (swap1[i] < swap2[i]) ? swap1[i] : swap2[i];
        int indirect_cost = min_val * 2;
        total_cost += (direct_cost < indirect_cost) ? direct_cost : indirect_cost;
    }
    return total_cost;
}

int main() {
    char line1[100000], line2[100000];
    int basket1[MAX_N], basket2[MAX_N];
    int n1 = 0, n2 = 0;

    // 读取第一行
    fgets(line1, sizeof(line1), stdin);
    char *token = strtok(line1, " \n");
    while (token != NULL) {
        basket1[n1++] = atoi(token);
        token = strtok(NULL, " \n");
    }

    // 读取第二行
    fgets(line2, sizeof(line2), stdin);
    token = strtok(line2, " \n");
    while (token != NULL) {
        basket2[n2++] = atoi(token);
        token = strtok(NULL, " \n");
    }

    long long result = minCost(basket1, n1, basket2, n2);
    printf("%lld\n", result);

    return 0;
}