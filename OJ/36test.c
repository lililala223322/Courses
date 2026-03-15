#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>          /* 1. 加头文件 */

bool isSymSub(const char *s, int i, int len)
{
    if (!s || len < 0 || i < 0) return false;
    int n = (int)strlen(s);
    if (i + len > n) return false;
    int l = i, r = i + len - 1;
    while (l < r) if (s[l++] != s[r--]) return false;
    return true;
}

/* 写数据到 36.exe 并把结果读回来 */
void run_solver(const char *input, char *output, int max_out)
{
    /* 写数据 */
    FILE *fw = _popen("36.exe", "w");
    if (!fw) { perror("_popen(write)"); exit(1); }
    fprintf(fw, "%s\n", input);
    fflush(fw);
    _pclose(fw);               /* 这里已经发送 EOF */

    /* 读结果 */
    FILE *fr = _popen("36.exe", "r");
    if (!fr) { perror("_popen(read)"); exit(1); }
    if (!fgets(output, max_out, fr)) output[0] = '\0';
    _pclose(fr);
    output[strcspn(output, "\r\n")] = '\0';
}

int main(void)
{
    srand((unsigned)time(NULL));
    const int MAXS = 2000;

    /* 2. 所有变量提前声明，避免 goto 后声明 */
    int core_len = 1 + rand() % 300;
    char *core    = malloc(core_len + 1);
    char *left, *right, *test, *got;
    int left_noise, right_noise;
    int max_len, n;
    bool correct;

    for (int i = 0; i < core_len; i++) core[i] = 'a' + rand() % 26;
    core[core_len] = '\0';
    for (int i = 0; i < core_len / 2; i++)
        core[core_len - 1 - i] = core[i];

    left_noise  = rand() % 200;
    right_noise = rand() % 200;
    if (left_noise == right_noise) right_noise++;

    left  = malloc(left_noise + 1);
    right = malloc(right_noise + 1);
    for (int i = 0; i < left_noise;  i++) left[i]  = 'a' + rand() % 26;
    for (int i = 0; i < right_noise; i++) right[i] = 'a' + rand() % 26;
    left[left_noise] = right[right_noise] = '\0';

    test = malloc(left_noise + core_len + right_noise + 1);
    sprintf(test, "%s%s%s", left, core, right);

    got = malloc(MAXS);
    run_solver(test, got, MAXS);

    max_len = 0;
    n = (int)strlen(test);
    for (int l = n; l > 0; l--) {
        for (int i = 0; i <= n - l; i++) {
            if (isSymSub(test, i, l)) { max_len = l; goto out; }
        }
    }
out:
    correct = (int)strlen(got) == max_len &&
              strstr(test, got) != NULL &&
              isSymSub(test, (int)(strstr(test, got) - test), (int)strlen(got));

    printf("Test  : %s\n", test);
    printf("Expect: (len=%d)\n", max_len);
    printf("Got   : %s\n", got);
    puts(correct ? "PASS" : "FAIL");

    free(core); free(left); free(right); free(test); free(got);
    return correct ? 0 : 1;
}