#include <stdio.h>
#include <math.h>

// 定义多项式函数
double y(double x, double p, double q, double r, double s) {
    return p * x * x * x + q * x * x + r * x + s;
}

// 二分查找根
double findRoot(double p, double q, double r, double s, double a, double b, double epsilon) {
    while (fabs(b - a) > epsilon) {
        double mid = (a + b) / 2.0;
        if (y(mid, p, q, r, s) == 0) {
            return mid;
        } else if (y(a, p, q, r, s) * y(mid, p, q, r, s) < 0) {
            b = mid;
        } else {
            a = mid;
        }
    }
    return (a + b) / 2.0;
}

int main() {
    double p, q, r, s;
    scanf("%lf %lf %lf %lf", &p, &q, &r, &s);

    double roots[3];
    double epsilon = 0.001; // 精度要求
    double start = -100, end = 100;

    // 寻找第一个根
    for (double i = start; i < end; i += epsilon) {
        if (y(i, p, q, r, s) * y(i + epsilon, p, q, r, s) < 0) {
            roots[0] = findRoot(p, q, r, s, i, i + epsilon, epsilon);
            break;
        }
    }

    // 寻找第二个根
    for (double i = start; i < end; i += epsilon) {
        if (y(i, p, q, r, s) * y(i + epsilon, p, q, r, s) < 0) {
            double root = findRoot(p, q, r, s, i, i + epsilon, epsilon);
            if (fabs(root - roots[0]) > epsilon) {
                roots[1] = root;
                break;
            }
        }
    }

    // 寻找第三个根
    for (double i = start; i < end; i += epsilon) {
        if (y(i, p, q, r, s) * y(i + epsilon, p, q, r, s) < 0) {
            double root = findRoot(p, q, r, s, i, i + epsilon, epsilon);
            if (fabs(root - roots[0]) > epsilon && fabs(root - roots[1]) > epsilon) {
                roots[2] = root;
                break;
            }
        }
    }

    // 排序根
    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (roots[i] > roots[j]) {
                double temp = roots[i];
                roots[i] = roots[j];
                roots[j] = temp;
            }
        }
    }

    // 输出结果
    printf("%.2f %.2f %.2f\n", roots[0], roots[1], roots[2]);

    return 0;
}