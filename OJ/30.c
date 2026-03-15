#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    double x, y;
} Point;

int compare_x(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x < p2->x) return -1;
    else if (p1->x > p2->x) return 1;
    else return 0;
}

int compare_y(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->y < p2->y) return -1;
    else if (p1->y > p2->y) return 1;
    else return 0;
}

double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double brute_force(Point points[], int left, int right) {
    double min_perimeter = DBL_MAX;
    for (int i = left; i <= right; i++) {
        for (int j = i + 1; j <= right; j++) {
            for (int k = j + 1; k <= right; k++) {
                double d1 = distance(points[i], points[j]);
                double d2 = distance(points[j], points[k]);
                double d3 = distance(points[i], points[k]);
                double perimeter = d1 + d2 + d3;
                if (perimeter < min_perimeter) {
                    min_perimeter = perimeter;
                }
            }
        }
    }
    return min_perimeter;
}

double min_perimeter_dc(Point points[], int left, int right) {
    if (right - left + 1 <= 5) {
        return brute_force(points, left, right);
    }

    int mid = (left + right) / 2;
    Point mid_point = points[mid];

    double left_min = min_perimeter_dc(points, left, mid);
    double right_min = min_perimeter_dc(points, mid + 1, right);
    double min_perimeter = MIN(left_min, right_min);

    Point strip[right - left + 1];
    int strip_size = 0;
    for (int i = left; i <= right; i++) {
        if (fabs(points[i].x - mid_point.x) < min_perimeter / 2) {
            strip[strip_size++] = points[i];
        }
    }

    qsort(strip, strip_size, sizeof(Point), compare_y);

    for (int i = 0; i < strip_size; i++) {
        for (int j = i + 1; j < strip_size && (strip[j].y - strip[i].y) < min_perimeter / 2; j++) {
            for (int k = j + 1; k < strip_size && (strip[k].y - strip[i].y) < min_perimeter / 2; k++) {
                double d1 = distance(strip[i], strip[j]);
                double d2 = distance(strip[j], strip[k]);
                double d3 = distance(strip[i], strip[k]);
                double perimeter = d1 + d2 + d3;
                if (perimeter < min_perimeter) {
                    min_perimeter = perimeter;
                }
            }
        }
    }

    return min_perimeter;
}

int main() {
    int M;
    scanf("%d", &M);
    Point points[M];
    for (int i = 0; i < M; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }

    qsort(points, M, sizeof(Point), compare_x);

    double min_perimeter = min_perimeter_dc(points, 0, M - 1);
    printf("%.6f\n", min_perimeter);

    return 0;
}