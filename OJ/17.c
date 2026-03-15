#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLength 20000   
#define MAXDepth 10      

char buf[MAXLength];      //最终答案
char *stkbuf[MAXDepth];  
int  stkrep[MAXDepth];   
int  top = 0;        //栈顶指针

int main(void)
{
    char line[MAXLength];
    if (!fgets(line, sizeof(line), stdin)) return 0;

    stkbuf[top] = buf;
    stkrep[top] = 1;
    top++;

    char *p = line;
    while (*p && *p != '\n') {
        if (*p == '[') {
            int d = 0;
            while (isdigit((unsigned char)*++p))
                d = d * 10 + (*p - '0');
            char *nb = (char *)calloc(MAXLength, 1);
            stkrep[top] = d;
            stkbuf[top] = nb;
            top++;
        }
        else if (*p == ']') {
            top--;
            int rep = stkrep[top];
            char *src = stkbuf[top];
            char *dst = stkbuf[top - 1];
            int sl = strlen(src);
            for (int i = 0; i < rep; i++)
                strcat(dst, src);
            free(src);
            p++;
        }
        else {
            int cur = top - 1;
            int len = strlen(stkbuf[cur]);
            stkbuf[cur][len]   = *p;
            stkbuf[cur][len+1] = '\0';
            p++;
        }
    }

    printf("%s\n", buf);
    return 0;
}