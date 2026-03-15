#include <stdio.h>
#include <stdlib.h>

/*
    1.升序排序
    2.对于每种数字组合，依次往后试，不对就break
*/

int compare_int(const void *a, const void *b) {
    return (*(int*)a - *(int*)b); // 升序
}

int main() {
    int n;
    scanf("%d",&n);
    int num[1000];
    static int count[10000];
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&num[i]);
    }

    qsort(num, n, sizeof(int), compare_int);
    for (int i = 0; i < n-2; i++)
    {
        for (int j = i+1; j < n-1; j++)
        {
            for (int k = j+1; k < n; k++)
            {
                if (num[i] + num[j] == num[k])
                    count[num[k]] = 1;
                else if (num[i] + num[j] < num[k])
                    break;
            }
            if (num[i] + num[j] > num[n-1])
                break;
        }
        if (num[i] + num[i+1] > num[n-1])
            break;
    }

    int sum = 0;
    for (int i = 0; i < 10000; i++)
    {
        sum += count[i];
    }

    printf("%d\n",sum);
    
}