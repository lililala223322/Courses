#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 比较函数，用于 qsort 降序
int cmp(const void *a, const void *b) {
    return -strcmp(*(const char **)a, *(const char **)b);
}

// 递归处理
char *make_largest(char *s) {
    int len = strlen(s);
    if (len == 0) {
        char *res = malloc(1);
        res[0] = '\0';
        return res;
    }
    
    // 分解成不可再分组件
    char **components = malloc(len * sizeof(char *));
    int comp_count = 0;
    int start = 0;
    int count = 0;
    
    for (int i = 0; i < len; i++) {
        if (s[i] == '1') count++;
        else count--;
        if (count == 0) {
            // 从 start 到 i 是一个不可再分组件
            int comp_len = i - start + 1;
            char *comp = malloc(comp_len + 1);
            // 复制组件
            strncpy(comp, s + start, comp_len);
            comp[comp_len] = '\0';
            // 递归处理内部：去掉首尾 1 和 0
            if (comp_len > 2) {
                char *inner = malloc(comp_len - 1);
                strncpy(inner, comp + 1, comp_len - 2);
                inner[comp_len - 2] = '\0';
                char *new_inner = make_largest(inner);
                // 构造新组件
                char *new_comp = malloc(comp_len + 1);
                new_comp[0] = '1';
                strcpy(new_comp + 1, new_inner);
                new_comp[comp_len - 1] = '0';
                new_comp[comp_len] = '\0';
                free(comp);
                free(inner);
                free(new_inner);
                comp = new_comp;
            }
            components[comp_count++] = comp;
            start = i + 1;
        }
    }
    
    // 按字典序降序排序组件
    qsort(components, comp_count, sizeof(char *), cmp);
    
    // 拼接结果
    int total_len = 0;
    for (int i = 0; i < comp_count; i++) {
        total_len += strlen(components[i]);
    }
    char *result = malloc(total_len + 1);
    result[0] = '\0';
    for (int i = 0; i < comp_count; i++) {
        strcat(result, components[i]);
        free(components[i]);
    }
    free(components);
    return result;
}

int main() {
    char s[1000];
    scanf("%s", s);
    char *res = make_largest(s);
    printf("%s\n", res);
    free(res);
    return 0;
}