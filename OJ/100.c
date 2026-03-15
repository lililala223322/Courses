/*
    ①算delta，然后往num里填充是不行的。
    ②num-A=delta1，A-num=delta2，num根据1削一遍再根据2进一遍
    */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <stddef.h>

#define MAX_LEN 2000
#define MAXT 1014

/* 存放 2、3、5、7 的指数 */
typedef struct {
    int e2, e3, e5, e7;
} Pool;

void sort_digits_range(char *arr, size_t n, size_t A, size_t B)
{
    if (A > B || B >= n) return;   /* 参数合法性检查 */

    int cnt[9] = {0};

    /* 1. 统计区间出现次数 */
    for (size_t i = A; i <= B; ++i)
        ++cnt[arr[i] - '1'];

    /* 2. 写回原区间 */
    size_t k = A;
    for (int d = 0; d < 9; ++d) {
        char ch = (char)('1' + d);
        for (int t = cnt[d]; t--; )
            arr[k++] = ch;
    }
}

void strrev_in_place(char *s)
{
    size_t i = 0, j = strlen(s);
    if (j-- == 0) return;        
    while (i < j) {
        char tmp = s[i];
        s[i++] = s[j];
        s[j--] = tmp;
    }
}

static void digit_to_pool(int d, Pool *p) {
    while (d % 2 == 0) { p->e2++; d /= 2; }
    while (d % 3 == 0) { p->e3++; d /= 3; }
    while (d % 5 == 0) { p->e5++; d /= 5; }
    while (d % 7 == 0) { p->e7++; d /= 7; }
}

void get_delta_pool(const char *num, const int *A, Pool *delta)
{
    Pool pool1 = {0}, pool2 = {0};

    /* 1. 分解 num 的每一位（跳过 '0' '1'） */
    for (const char *pc = num; *pc; ++pc) {
        if (*pc == '0' || *pc == '1') continue;
        digit_to_pool(*pc - '0', &pool1);
    }

    /* 2. 分解 A：遇到 0 就停 */
    for (const int *p = A; *p != 0; ++p)
        digit_to_pool(*p, &pool2);

    delta->e2 = pool2.e2 > pool1.e2 ? pool2.e2 - pool1.e2 : 0;
    delta->e3 = pool2.e3 > pool1.e3 ? pool2.e3 - pool1.e3 : 0;
    delta->e5 = pool2.e5 > pool1.e5 ? pool2.e5 - pool1.e5 : 0;
    delta->e7 = pool2.e7 > pool1.e7 ? pool2.e7 - pool1.e7 : 0;
}

static char has_large[MAXT + 1];

long long digit_prod(const char *s) {
    long long prod = 1;
    for (int i = 0; s[i]; i++) prod *= (s[i] - '0');
    return prod;
}

/* 初始化：筛出 9~MAXT 的所有质数，并把它们的所有倍数都标记为 1 */
static void init_large_prime_flag(void)
{
    static char is_prime[MAXT + 1];
    int i, j;

    for (i = 2; i <= MAXT; ++i) is_prime[i] = 1;

    /* 埃氏筛 */
    for (i = 2; i * i <= MAXT; ++i) {
        if (is_prime[i]) {
            for (j = i * i; j <= MAXT; j += i)
                is_prime[j] = 0;
        }
    }

    for (i = 10; i <= MAXT; ++i) {  
        if (is_prime[i]) {
            for (j = i; j <= MAXT; j += i)
                has_large[j] = 1;
        }
    }
}

int has_large_prime(int t)   // t ≤ 1014
{
    /* 只做一次预处理 */
    static int inited = 0;
    if (!inited) {
        init_large_prime_flag();
        inited = 1;
    }
    return has_large[t];
}

int good(const char *s, long long t) {
    for (const char *p = s; *p; ++p) if (*p == '0') return 0;
    return digit_prod(s) % t == 0;
}

void greedy_factor(int t, int A[]) 
{
    int cnt = 0;
    while (t > 1) {
        /* 从大到小依次尝试 9,8,...,2 */
        for (int d = 9; d >= 2; --d) {
            while (t % d == 0) {
                A[cnt++] = d;   
                t /= d;         
            }
        }
        if (t > 1) {
            A[cnt++] = t;
            break;
        }
    }
    return;  
}

int fill_num(char *num, Pool *delta)
{
    //逆序，从首位开始做
    strrev_in_place(num);
    int num_lenth = strlen(num);

    // 填充
    for (int i = 0; 1; )
    {
        if (num[i] == '0')
            num[i] = '1';

        if (num[i] == '1')
        {
            // 1-9
            if (delta->e3 >= 2)
            {
                num[i++] = '9';
                delta->e3 -= 2;
            }
            // 1-8
            else if (delta->e2 >= 3)
            {
                num[i++] = '8';
                delta->e2 -= 3;
            }
            // 1-7
            else if (delta->e7 >= 1)
            {
                num[i++] = '7';
                delta->e7 -= 1;
            }
            // 1-5
            else if (delta->e5 >= 1)
            {
                num[i++] = '5';
                delta->e5 -= 1;
            }
            // 1-6
            else if (delta->e2 >= 1 && delta->e3 >=1)
            {
                num[i++] = '6';
                delta->e2 -= 1;
                delta->e3 -= 1;
            }
            // 1-4
            else if (delta->e2 >= 2)
            {
                num[i] = '4';
                delta->e2 -= 2;
            }
            // 1-3
            else if (delta->e3 >= 1)
            {
                num[i] = '3';
                delta->e3 -= 1;
            }
            // 1-2
            else if (delta->e2 >= 1)
            {
                num[i] = '2';
                delta->e2 -= 1;
            }
        }
        else if (num[i] == '2')
        {
            // 2-8
            if (delta->e2 >= 2)
            {
                num[i++] = '8';
                delta->e2 -= 2;
            }
            // 2-6
            else if (delta->e3 >= 1)
            {
                num[i++] = '6';
                delta->e3 -= 1;
            }
            // 2-4
            else if (delta->e2 >= 1)
            {
                num[i] = '4';
                delta->e2 -= 1;
            }
        }
        else if (num[i] == '3')
        {
            // 3-9
            if (delta->e3 >= 1)
            {
                num[i++] = '9';
                delta->e3 -= 1;
            }
            // 3-6
            else if (delta->e2 >= 1)
            {
                num[i++] = '6';
                delta->e2 -= 1;
            }
        }
        else if (num[i] == '4' && delta->e2 >= 1)
        {
            num[i++] = '8';
            delta->e2 -= 1;
        }
        else
            i++;
        
        if (delta->e2 + delta->e3 + delta->e5 + delta->e7 == 0)
            return num_lenth;
        else if (i == num_lenth)
        {
            num[num_lenth++] = '1';
            num[num_lenth] = 0;
        }
    }
    
}

int main(void) 
{
    char num[MAX_LEN];
    long long t;
    static int A[10]; // 1014 < 2^10
    scanf("%s %d", num, &t);
    char num2[MAX_LEN];
    strcpy(num2,num);

    /* 0. 本身已满足且不含0 */
    if (good(num2, t)) { printf("%s\n", num2); return 0; }

    /* 1. t 含>9质因子 → -1 */
    if (has_large_prime(t)) { printf("-1\n"); return 0; }

    greedy_factor(t, A);
    Pool delta;
    get_delta_pool(num2, A, &delta);
    int len = fill_num(num2, &delta);
    strrev_in_place(num2);
    for (int i = 0; i < len; i++)
    {
        if (num2[i] > num[i])
        {
            sort_digits_range(num2, MAX_LEN, i+1, len);
            break;
        }
    }

    printf("%s",num2);

    return 0;
}