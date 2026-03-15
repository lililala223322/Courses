#include <stdio.h>
#include <string.h>
#include <unordered_map>

using namespace std;

const int MOD = 1000000007;
const int JMAX = 100000;  // 经验值，足够大

int k;

struct State {
    int pos;
    int jump;
    int last;  // 0: 上次不是向下走；1: 是向下走
    bool operator==(const State& o) const {
        return pos == o.pos && jump == o.jump && last == o.last;
    }
};

namespace std {
    template<>
    struct hash<State> {
        size_t operator()(const State& s) const {
            return hash<int>()(s.pos) ^ hash<int>()(s.jump) ^ hash<int>()(s.last);
        }
    };
}

unordered_map<State, long long> memo;

long long dfs(int pos, int jump, int last) {
    if (pos == k) return 1;
    if (pos < 0 || pos > k + JMAX) return 0;  // 剪枝：太远就放弃
    if (jump > JMAX) return 0;  // jump 太大也放弃

    State state = {pos, jump, last};
    if (memo.count(state)) return memo[state];

    long long res = 0;

    // 操作1：向下走（不能连续，不能从0向下走）
    if (pos > 0 && last == 0) {
        res += dfs(pos - 1, jump, 1);
        res %= MOD;
    }

    // 操作2：向上跳
    int new_pos = pos + 2 * jump;
    if (new_pos <= k + JMAX) {  // 不要跳太远
        res += dfs(new_pos, jump + 1, 0);
        res %= MOD;
    }

    return memo[state] = res;
}

int main() {
    scanf("%d", &k);
    printf("%lld\n", dfs(1, 0, 0));
    return 0;
}