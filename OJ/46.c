#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 100005

int main(void){
    char s[MAXN], chars[27]; 
    static int val[26];          
    int  vals[26];

    if(!fgets(s, MAXN, stdin)) return 0;
    s[strcspn(s, "\n")] = 0;     

    if(!fgets(chars, 27, stdin)) return 0;
    chars[strcspn(chars, "\n")] = 0;
    int m = strlen(chars);

    for(int i = 0; i < m; i++) scanf("%d", &vals[i]);

    for(int i = 0; i < 26; i++) val[i] = i + 1;

    for(int i = 0; i < m; i++){
        int idx = chars[i] - 'a';
        val[idx] = vals[i];
    }

    /*  Kadane 算法 */
    long long ans = 0, cur = 0;
    int len = strlen(s);
    for(int i = 0; i < len; i++){
        int v = val[ s[i] - 'a' ];
        cur += v;
        if(cur > ans) ans = cur;
        if(cur < 0)   cur = 0;   
    }

    printf("%lld\n", ans);
    return 0;
}