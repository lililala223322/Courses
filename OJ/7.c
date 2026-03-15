#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int Furthest(float avg, float num[], int n) {

    double max_diff = -1;
    int furthest_idx = -1;

    // 找到与均值差异最大的数
    for (int i = 0; i < n; i++) {
        double diff = fabs(num[i] - avg);
        
        if (diff > max_diff) {
            max_diff = diff;
            furthest_idx = i;
        }
    }
    
    return furthest_idx;
}

int main() {
    int n;
    scanf("%d",&n);
    float num[10000], sum = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%f",&num[i]);
        sum += num[i];
    }
    float avg = sum/n;

    int f1 = Furthest(avg, num, n);
    if (num[f1] == sum)
    {
        num[f1] = avg;
        printf("%.0f",num[Furthest(avg, num, n)]);
    }
    else
    {
        printf("%.0f",num[f1]);
    }

    return 0;
}