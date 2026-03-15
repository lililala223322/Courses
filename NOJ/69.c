//三元搜索

#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);

    int num[n];
    for (int i = 0; i < n; i++)
        scanf("%d",&num[i]);
    
    int key;
    scanf("%d",&key);

    //查找
    for (int i = 0; i < n; i++)
        if ( num[i] == key ) {
            printf("%d in [%d]",key,i);
            return 0;
        }

    //找不到会出循环
    printf("%d in [-1]",key);    
}