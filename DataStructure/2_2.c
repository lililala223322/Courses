#include <stdio.h>

void Union(int A[], int B[], int C[], int numberOfA, int numberOfB, int *numberOfC)
{
    int i = 0, j = 0;
    *numberOfC = 0;

    while (i < numberOfA && j < numberOfB)
    {
        if (A[i] < B[j]) {
            C[(*numberOfC)++] = A[i++];
        } else if (A[i] > B[j]) {
            C[(*numberOfC)++] = B[j++];
        } else {
            // A[i] == B[j]，只插入一次
            C[(*numberOfC)++] = A[i];
            i++;
            j++;
        }
    }

    // 将A中剩余的元素插入C
    while (i < numberOfA) {
        C[(*numberOfC)++] = A[i++];
    }
 
    // 将B中剩余的元素插入C
    while (j < numberOfB) {
        C[(*numberOfC)++] = B[j++];
    }
    
    return;
}

int main()
{
    int A[] = {1,3,5,7};
    int B[] = {1,2,3,4,5,7};
    int numberOfA = sizeof(A) / sizeof(A[0]);
    int numberOfB = sizeof(B) / sizeof(B[0]);

    int C[numberOfA + numberOfB];
    int numberOfC;
    
    Union(A, B , C, numberOfA, numberOfB, &numberOfC);

    // 输出并集C
    for (int i = 0; i < numberOfC; i++) {
        printf("%d ", C[i]);
    }
 
    return 0;
}