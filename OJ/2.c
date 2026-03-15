#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 1000

void process_string(char *s, char *result) {
    int top = -1;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] != '#') {
            top++;
            result[top] = s[i];
        } else {
            if (top >= 0) {
                top--;
            }
        }
    }
    result[top + 1] = '\0';
}

int main() {
    char s1[MAX_LEN], s2[MAX_LEN];
    scanf("%s %s", s1, s2);
    
    char res1[MAX_LEN], res2[MAX_LEN];
    process_string(s1, res1);
    process_string(s2, res2);
    
    if (strcmp(res1, res2) == 0) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return 0;
}