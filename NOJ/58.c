#include<stdio.h>
#include<string.h>

void subreplace(char *str, const char *olds, const char *news) 
{
    int old_len = strlen(olds);
    int new_len = strlen(news);
    char *pos = str;
    while ((pos = strstr(pos, olds)) != NULL) 
    {
        memmove(pos + new_len, pos + old_len, strlen(pos +
        old_len) + 1);
        memcpy(pos, news, new_len);
        pos += new_len;
    }
}

int main()
{
    char str[2000]={0} , olds[2000]={0} , news[2000]={0};

    scanf("%[^\n] %[^\n] %[^\n]", str, olds, news);

    subreplace(str,olds,news); 

    for (int i = 0; str[i] ; i++)
        printf("%c",str[i]);
    
}