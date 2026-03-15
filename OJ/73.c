#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[505];
    if (!fgets(s, sizeof(s), stdin)) return 0;

    int cnt[128] = {0};
    int maxFreq = 0, total = 0;

    for (int i = 0; s[i] && s[i] != '\n'; ++i) {
        int c = (unsigned char)s[i];
        ++cnt[c];
        if (cnt[c] > maxFreq) maxFreq = cnt[c];
        ++total;
    }

    puts(maxFreq <= (total + 1) / 2 ? "1" : "0");
    return 0;
}