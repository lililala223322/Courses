#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

bool isPreorderBST(const int *pre, int n)
{
    if (n == 0) return true;

    int *stk = malloc(n * sizeof(int));
    int top = 0;          /* 栈顶指针 */
    stk[0] = pre[0];

    int low = 0;          /* 全局下界：右子树节点必须 > low */
    for (int i = 1; i < n; ++i)
    {
        int x = pre[i];
        if (x <= low) { free(stk); return false; }   

        while (top >= 0 && stk[top] < x)
            low = stk[top--];

        stk[++top] = x;   /* 当前节点入栈 */
    }
    free(stk);
    return true;
}

/* -------------------------- 读行并拆数 -------------------------- */
int main(void)
{
    char line[5000];
    if (!fgets(line, sizeof(line), stdin))     /* 读整行 */
        return 0;

    int arr[2000], n = 0;
    char *p = line;
    while (*p) {
        /* 跳过连续空白 */
        while (isspace((unsigned char)*p)) ++p;
        if (*p == '\0') break;

        /* 拆一个整数 */
        errno = 0;
        char *end;
        long val = strtol(p, &end, 10);
        if (end == p || errno != 0) break;   
        arr[n++] = (int)val;
        p = end;
    }

    printf("%s\n", isPreorderBST(arr, n) ? "true" : "false");
    return 0;
}