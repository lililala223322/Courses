#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 16
#define BOX_SIZE 4

char board[SIZE][SIZE];
// 函数声明
bool preprocess(int testCase);
void printResult();
bool solveSudoku();

// 计算指定位置可以填入的候选字母的位掩码
int getCandidates(int row, int col) {
    int used = 0;
    
    // 检查行
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] != '-') {
            used |= (1 << (board[row][i] - 'A'));
        }
    }
    
    // 检查列
    for (int i = 0; i < SIZE; i++) {
        if (board[i][col] != '-') {
            used |= (1 << (board[i][col] - 'A'));
        }
    }
    
    // 检查4×4的小方格
    int boxRow = (row / BOX_SIZE) * BOX_SIZE;
    int boxCol = (col / BOX_SIZE) * BOX_SIZE;
    for (int i = boxRow; i < boxRow + BOX_SIZE; i++) {
        for (int j = boxCol; j < boxCol + BOX_SIZE; j++) {
            if (board[i][j] != '-') {
                used |= (1 << (board[i][j] - 'A'));
            }
        }
    }
    
    return ((1 << SIZE) - 1) & ~used;  // 返回可用字母的位掩码
}

bool findHiddenSingles() {
    bool updated = false;

    // 检查每一行
    for (int row = 0; row < SIZE; row++) {
        int letterCount[SIZE] = {0};
        int letterPos[SIZE] = {-1};

        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == '-') {
                int candidates = getCandidates(row, col);
                for (int k = 0; k < SIZE; k++) {
                    if (candidates & (1 << k)) {
                        letterCount[k]++;
                        letterPos[k] = col;
                    }
                }
            }
        }

        for (int k = 0; k < SIZE; k++) {
            if (letterCount[k] == 1 && letterPos[k] != -1) {
                int col = letterPos[k];
                board[row][col] = 'A' + k;
                printf("Hidden Single: Fill (%d,%d) with %c\n", row, col, 'A' + k);
                printResult();
                printf("\n");
                updated = true;
            }
        }
    }

    // 检查每一列（类似逻辑）
    for (int col = 0; col < SIZE; col++) {
        int letterCount[SIZE] = {0};
        int letterPos[SIZE] = {-1};

        for (int row = 0; row < SIZE; row++) {
            if (board[row][col] == '-') {
                int candidates = getCandidates(row, col);
                for (int k = 0; k < SIZE; k++) {
                    if (candidates & (1 << k)) {
                        letterCount[k]++;
                        letterPos[k] = row;
                    }
                }
            }
        }

        for (int k = 0; k < SIZE; k++) {
            if (letterCount[k] == 1 && letterPos[k] != -1) {
                int row = letterPos[k];
                board[row][col] = 'A' + k;
                printf("Hidden Single: Fill (%d,%d) with %c\n", row, col, 'A' + k);
                printResult();
                printf("\n");
                updated = true;
            }
        }
    }

    // 检查每个4x4宫（类似逻辑）
    for (int boxRow = 0; boxRow < BOX_SIZE; boxRow++) {
        for (int boxCol = 0; boxCol < BOX_SIZE; boxCol++) {
            int letterCount[SIZE] = {0};
            int letterPos[SIZE][2] = {{-1, -1}};

            for (int r = 0; r < BOX_SIZE; r++) {
                for (int c = 0; c < BOX_SIZE; c++) {
                    int row = boxRow * BOX_SIZE + r;
                    int col = boxCol * BOX_SIZE + c;
                    if (board[row][col] == '-') {
                        int candidates = getCandidates(row, col);
                        for (int k = 0; k < SIZE; k++) {
                            if (candidates & (1 << k)) {
                                letterCount[k]++;
                                letterPos[k][0] = row;
                                letterPos[k][1] = col;
                            }
                        }
                    }
                }
            }

            for (int k = 0; k < SIZE; k++) {
                if (letterCount[k] == 1 && letterPos[k][0] != -1) {
                    int row = letterPos[k][0];
                    int col = letterPos[k][1];
                    board[row][col] = 'A' + k;
                    printf("Hidden Single: Fill (%d,%d) with %c\n", row, col, 'A' + k);
                    printResult();
                    printf("\n");
                    updated = true;
                }
            }
        }
    }

    return updated;
}

// 计算位掩码中1的个数（候选字母数量）
int countBits(int mask) {
    int count = 0;
    while (mask) {
        count += mask & 1;
        mask >>= 1;
    }
    return count;
}

// 找到候选字母数量最少的空格
bool findMinCandidateCell(int *row, int *col) {
    int minCandidates = SIZE + 1;
    bool found = false;
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == '-') {
                int candidates = getCandidates(i, j);
                int count = countBits(candidates);
                
                if (count < minCandidates) {
                    minCandidates = count;
                    *row = i;
                    *col = j;
                    found = true;
                    
                    if (count == 1) {  // 如果找到唯一候选，立即返回
                        return true;
                    }
                }
            }
        }
    }
    
    return found;
}

bool preprocess(int testCase) {
    int step = 1;
    bool changedInRound;

    do {
        changedInRound = false;

        // ✅ 第一轮：唯一候选数（Naked Single）
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == '-') {
                    int candidates = getCandidates(i, j);
                    int count = countBits(candidates);

                    if (count == 1) {
                        for (int k = 0; k < SIZE; k++) {
                            if (candidates & (1 << k)) {
                                board[i][j] = 'A' + k;
                                printf("Test Case %d - Step %d: Naked Single at (%d,%d) -> %c\n", testCase, step++, i, j, 'A' + k);
                                printResult();
                                printf("\n");
                                changedInRound = true;
                                break;
                            }
                        }
                    } else if (count == 0) {
                        return false; // 无解
                    }
                }
            }
        }

        // ✅ 第二轮：隐藏唯一候选数（Hidden Single）
        if (findHiddenSingles(step++, testCase)) {
            changedInRound = true;
        }

    } while (changedInRound); // 🔁 只要本轮有填充，就继续下一轮

    return true;
}

// 优化后的回溯法
bool solveSudoku() {
    int row, col;
    
    // 找到候选字母数量最少的空格
    if (!findMinCandidateCell(&row, &col)) {
        return true;  // 所有空格都已填满
    }
    
    int candidates = getCandidates(row, col);
    
    // 尝试每个候选字母
    for (int k = 0; k < SIZE; k++) {
        if (candidates & (1 << k)) {
            board[row][col] = 'A' + k;
            
            if (solveSudoku()) {
                return true;
            }
            
            board[row][col] = '-';  // 回溯
        }
    }
    
    return false;
}

// 读取输入数据
void readInput() {
    for (int i = 0; i < SIZE; i++) {
        scanf("%s", board[i]);
    }
}

void printResult() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);  // 加空格更清晰
        }
        printf("\n");
    }
}

int main() {
    int k;
    scanf("%d", &k);
    
    for (int test = 0; test < k; test++) {
        // 读取空白行（如果有的话）
        if (test > 0) {
            char blankLine[2];
            fgets(blankLine, 2, stdin);
        }
        
        readInput();
        
        if (preprocess(test + 1)) {
            solveSudoku();
        }
        
        printResult();
        
        if (test < k - 1) {
            printf("\n");
        }
    }
    
    return 0;
}