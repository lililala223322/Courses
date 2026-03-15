#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 1000000

typedef struct {
    int value;
    int steps;
} Node;

Node queue[MAX_SIZE];
int front = 0, rear = 0;
int visited[MAX_SIZE];

void enqueue(int value, int steps) {
    queue[rear].value = value;
    queue[rear].steps = steps;
    rear++;
}

Node dequeue() {
    return queue[front++];
}

int is_empty() {
    return front == rear;
}

int min_operations(int a, int b) {
    if (a == b) return 0;
    
    // 初始化visited数组
    for (int i = 0; i < MAX_SIZE; i++) {
        visited[i] = 0;
    }
    front = rear = 0;
    
    enqueue(a, 0);
    visited[a] = 1;
    
    while (!is_empty()) {
        Node current = dequeue();
        int current_value = current.value;
        int current_steps = current.steps;
        
        // 检查所有可能的操作
        int next_values[4];
        int count = 0;
        
        // 操作1: 除以11（如果是11的倍数）
        if (current_value % 11 == 0) {
            next_values[count++] = current_value / 11;
        }
        
        // 操作2: 除以5（如果是5的倍数）
        if (current_value % 5 == 0) {
            next_values[count++] = current_value / 5;
        }
        
        // 操作3: 减1
        next_values[count++] = current_value - 1;
        
        // 操作4: 加1
        next_values[count++] = current_value + 1;
        
        for (int i = 0; i < count; i++) {
            int next_value = next_values[i];
            
            // 如果找到目标值，返回步数
            if (next_value == b) {
                return current_steps + 1;
            }
            
            // 检查边界条件和是否已访问
            if (next_value >= 0 && next_value < MAX_SIZE && !visited[next_value]) {
                visited[next_value] = 1;
                enqueue(next_value, current_steps + 1);
            }
        }
    }
    
    return -1;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    
    int result = min_operations(a, b);
    printf("%d\n", result);
    
    return 0;
}