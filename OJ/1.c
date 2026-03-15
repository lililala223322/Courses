#include <stdio.h>

int main() {
    char s[10005];
    fgets(s, sizeof(s), stdin);   

    int count = 0, last = 0;
    for (int i = 0; s[i] && s[i] != '\n'; ++i) { 
        if (s[i] == ' ') {
            count = 0;       
        } else {
            ++count;          
            last = count;       
        }
    }
    printf("%d\n", last);
    return 0;
}