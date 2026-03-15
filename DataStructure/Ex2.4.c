#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int row, col, value;
} Triple;

typedef struct {
    Triple *data;
    int rows, cols, nums;
} Matrix;

// 读取稀疏矩阵
Matrix readMatrix() {
    Matrix matrix;
    scanf("%d %d", &matrix.rows, &matrix.cols);
    
    int capacity = 10; // 初始容量
    matrix.data = (Triple *)malloc(capacity * sizeof(Triple));
    matrix.nums = 0;

    while (1) {
        int row, col, value;
        scanf("%d %d %d", &row, &col, &value);
        if (row == 0 && col == 0 && value == 0) {
            break;
        }
        if (matrix.nums >= capacity) {
            capacity *= 2;
            matrix.data = (Triple *)realloc(matrix.data, capacity * sizeof(Triple));
        }
        matrix.data[matrix.nums].row = row;
        matrix.data[matrix.nums].col = col;
        matrix.data[matrix.nums].value = value;
        matrix.nums++;
    }

    return matrix;
}
// 稀疏矩阵乘法
Matrix multiplyMatrix(Matrix A, Matrix B) {
    if (A.cols != B.rows) {
        printf("这两个矩阵无法参与乘法\n");
        exit(EXIT_FAILURE);
    }

    Matrix C;
    C.rows = A.rows;
    C.cols = B.cols;
    C.nums = 0;
    C.data = (Triple *)malloc(10 * sizeof(Triple)); // 初始容量

    int capacity = 10;

    // 使用一个辅助数组来存储结果矩阵的累加值
    int **result = (int **)calloc((A.rows + 1), sizeof(int *));
    for (int i = 1; i <= A.rows; i++) {
        result[i] = (int *)calloc((B.cols + 1), sizeof(int));
    }

    // 计算乘积并累加到result中
    for (int i = 0; i < A.nums; i++) {
        for (int j = 0; j < B.nums; j++) {
            if (A.data[i].col == B.data[j].row) {
                int newRow = A.data[i].row;
                int newCol = B.data[j].col;
                result[newRow][newCol] += A.data[i].value * B.data[j].value;
            }
        }
    }

    // 将result中的非零值转换为三元组形式
    for (int i = 1; i <= A.rows; i++) {
        for (int j = 1; j <= B.cols; j++) {
            if (result[i][j] != 0) {
                if (C.nums >= capacity) {
                    capacity *= 2;
                    C.data = (Triple *)realloc(C.data, capacity * sizeof(Triple));
                }
                C.data[C.nums].row = i;
                C.data[C.nums].col = j;
                C.data[C.nums].value = result[i][j];
                C.nums++;
            }
        }
        free(result[i]); // 释放每一行的内存
    }
    free(result); // 释放行指针数组

    return C;
}

int main() {
    Matrix A = readMatrix();
    Matrix B = readMatrix();

    Matrix C = multiplyMatrix(A, B);

    for (int i = 0; i < C.nums; i++) {
        printf("%d %d %d\n", C.data[i].row, C.data[i].col, C.data[i].value);
    }

    return 0;
}