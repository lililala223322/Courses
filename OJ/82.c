#include <stdio.h>

static inline int leap(int y) {
    return (y % 4 == 0 && y % 100) || (y % 400 == 0);
}

static const int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static int valid_date(int y, int m, int d) {
    if (m < 1 || m > 12) return 0;
    int md = days[m] + (m == 2 && leap(y));
    return d >= 1 && d <= md;
}

static int pack(int y, int m, int d) {
    return y * 10000 + m * 100 + d;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    int pal = 0, sym = 0;
    int y0 = N / 10000;

    for (int y = y0; y <= 9999; ++y) {
        char sy[5];
        sprintf(sy, "%04d", y);

        int rp_m = (sy[3] - '0') * 10 + (sy[2] - '0');
        int rp_d = (sy[1] - '0') * 10 + (sy[0] - '0');
        if (!pal && valid_date(y, rp_m, rp_d)) {
            int cand = pack(y, rp_m, rp_d);
            if (cand > N) pal = cand;
        }
        if (pal) break;
    }

    for (int A = 0; A <= 9; A++) {
        for (int B = 0; B <= 9; B++) {
            if (A == B) continue; 
            int year = A * 1000 + B * 100 + A * 10 + B;
            int month = B * 10 + A;
            int day = B * 10 + A;
            
            if (valid_date(year, month, day)) {
                int cand = pack(year, month, day);
                if (cand > N) {
                    if (sym == 0 || cand < sym) {
                        sym = cand;
                    }
                }
            }
        }
    }

    if (sym == 0) {
        for (int A = 0; A <= 9; A++) {
            int year = A * 1000 + A * 100 + A * 10 + A;
            int month = A * 10 + A;
            int day = A * 10 + A;
            
            if (valid_date(year, month, day)) {
                int cand = pack(year, month, day);
                if (cand > N) {
                    if (sym == 0 || cand < sym) {
                        sym = cand;
                    }
                }
            }
        }
    }

    printf("%08d\n%08d\n", pal, sym);
    return 0;
}