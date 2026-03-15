#include <stdio.h>

typedef struct {
    int row;
    int col;
    int value;
} Triple;

#define MAX_TERMS 100  // 假设最多有100个非零元素

void transposeMatrix(Triple original[], Triple transposed[], int n, int m, int numTerms) {
    int k = 0;
    for (int j = 0; j < m; j++) {  // 遍历，然后按对称的方式转置
        for (int i = 0; i < numTerms; i++) {
            if (original[i].col == j) {
                transposed[k].row = original[i].col;
                transposed[k].col = original[i].row;
                transposed[k].value = original[i].value;
                k++;
            }
        }
    }
}

int main() {
    int n, m;
    Triple original[MAX_TERMS];
    Triple transposed[MAX_TERMS];
    int numTerms = 0;

    // 输入矩阵的行数和列数
    scanf("%d %d", &n, &m);

    // 输入矩阵的三元组
    while (1) {
        Triple temp;
        scanf("%d %d %d", &temp.row, &temp.col, &temp.value);
        if (temp.row == 0 && temp.col == 0 && temp.value == 0) {
            break;
        }
        original[numTerms++] = temp;
    }

    // 转置
    transposeMatrix(original, transposed, n, m, numTerms);

    // 输出
    for (int i = 0; i < numTerms; i++) {
        printf("%d %d %d\n", transposed[i].row, transposed[i].col, transposed[i].value);
    }

    return 0;
}