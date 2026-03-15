#include <stdio.h>

int a, half;
char buf[32];
/* 旋转映射表 */
const char rot_map[128] = {
    ['0'] = '0', ['1'] = '1', ['8'] = '8',
    ['6'] = '9', ['9'] = '6'
};

static void output(void)
{
    for (int i = 0; i < half; ++i) putchar(buf[i]);
    if (a & 1) putchar(buf[half]);                 /* 中间字符 */
    for (int i = half - 1; i >= 0; --i)            /* 右半逆序 */
        putchar(rot_map[(unsigned char)buf[i]]);
    putchar(' ');
}

static const char odd_tbl[3] = {'0','1','8'};
static const char normal_tbl[5] = {'0','1','6','8','9'};

static void dfs(int pos, int first)
{
    if (pos == half) {
        if (a & 1) {
            for (int k = 0; k < 3; ++k) {
                buf[half] = odd_tbl[k];
                output();
            }
        } else {
            output();
        }
        return;
    }
    for (int k = 0; k < 5; ++k) {
        char c = normal_tbl[k];
        if (first && c == '0') continue;   /* 高位不能为 0 */
        buf[pos] = c;
        dfs(pos + 1, 0);
    }
}

int main(void)
{
    if (scanf("%d", &a) != 1) return 0;
    half = a / 2;
    if (a == 1) {                /* 长度 1 特判 */
        puts("0 1 8");
        return 0;
    }
    dfs(0, 1);
    putchar('\n');
    return 0;
}
