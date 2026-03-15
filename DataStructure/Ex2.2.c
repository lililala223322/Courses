#include <stdio.h>

typedef struct {
    int row;
    int col;
    int value;
} Triple;

int MatrixAdd(Triple A[], int t1, Triple B[], int t2, Triple C[]) {
    int i = 0, j = 0;
    int k = 0;

    // 在A、B的共有长度内执行以下操作
    while (i < t1 && j < t2) {
        // 非重复则挪动，重复则相加
        if (A[i].row < B[j].row || (A[i].row == B[j].row && A[i].col < B[j].col)) {
            C[k++] = A[i++];
        } else if (B[j].row < A[i].row || (B[j].row == A[i].row && B[j].col < A[i].col)) {
            C[k++] = B[j++];
        } else {
            int sum = A[i].value + B[j].value;
            if (sum != 0) {
                C[k].row = A[i].row;
                C[k].col = A[i].col;
                C[k].value = sum;
                k++;
            }
            i++;
            j++;
        }
    }

    // 把A剩下的元素添加到C中
    while (i < t1) {
        C[k++] = A[i++];
    }

    // 把B剩下的元素添加到C中
    while (j < t2) {
        C[k++] = B[j++];
    }

    return k;
}

int main() {
    int m, n, t1, t2;
    scanf("%d %d %d %d", &m, &n, &t1, &t2);

    // 输入
    Triple A[t1], B[t2], C[t1 + t2];
    for (int i = 0; i < t1; i++) {
        scanf("%d %d %d", &A[i].row, &A[i].col, &A[i].value);
    }

    for (int i = 0; i < t2; i++) {
        scanf("%d %d %d", &B[i].row, &B[i].col, &B[i].value);
    }

    // 相加
    int k = MatrixAdd(A, t1, B, t2, C);

    // 输出
    for (int p = 0; p < k; p++) {
        printf("%d %d %d\n", C[p].row, C[p].col, C[p].value);
    }

    return 0;
}