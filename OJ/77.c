#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int canFinish(long long T, int waterVolume, int workerTimes[], int workerCount) {
    long long total = 0;
    for (int i = 0; i < workerCount; i++) {
        long long x = (long long)((-1 + sqrt(1 + 8.0 * T / workerTimes[i])) / 2);
        total += x;
        if (total >= waterVolume) {
            return 1;
        }
    }
    return total >= waterVolume;
   }

long long minTimeToCarryWater(int waterVolume, int workerTimes[], int workerCount) {
    if (workerCount == 0) return 0;
    int maxEfficiency = workerTimes[0];
    for (int i = 1; i < workerCount; i++) {
        if (workerTimes[i] < maxEfficiency) {
            maxEfficiency = workerTimes[i];
        }
    }
    long long left = 0;
    long long right = (long long)maxEfficiency * waterVolume * (waterVolume + 1) / 2;
    
    // 二分查找
    while (left < right) {
        long long mid = left + (right - left) / 2;
        if (canFinish(mid, waterVolume, workerTimes, workerCount)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

int main() {
    int waterVolume;
    scanf("%d", &waterVolume);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    int workerTimes[10000];
    int workerCount = 0;
    char buffer[1000000]; 
    
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        char *ptr = buffer;
        int num;

        while (sscanf(ptr, "%d", &num) == 1) {
            if (workerCount < 10000) {
                workerTimes[workerCount++] = num;
            }

            while (*ptr && *ptr != ' ' && *ptr != '\n' && *ptr != '\r') ptr++;
            while (*ptr == ' ' || *ptr == '\n' || *ptr == '\r') ptr++;
            
            if (*ptr == '\0') break;
        }
    }
    
    // 计算并输出结果
    long long result = minTimeToCarryWater(waterVolume, workerTimes, workerCount);
    printf("%lld\n", result);
    
    return 0;
}