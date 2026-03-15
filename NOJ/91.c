#include<stdio.h>

int main()
{
    char s[1001]={0};
    scanf("%s",s);

    //统计长度
    int n=0;
    while (s[n])
        n++;
    n--;

    int mid , m;
    if (n%2)
    {
        mid = (n-1)/2;//奇数，指向正中间
        m = 1;
    }
    else
    {
        mid = (n-2)/2;//偶数，指向正中间的左侧
        m = 2;
    }

    int left1 = 0 , right1 = mid , left2 = mid + m , right2 = n;

    //左侧冒泡
    for (int i = left1; i < right1; i++)
    {
        for (int j = i; j <= right1; j++)
        {
            if (s[i] < s[j]) 
            {
                int t = s[i];
                s[i] = s[j];
                s[j] = t;
            }
        }
    }

    while (left2 < right2)
    {
        int t = s[left2];
        s[left2] = s[right2];
        s[right2] = t;
        left2++;
        right2--;
    }

    printf("%s",s);    
    
    return 0;
}