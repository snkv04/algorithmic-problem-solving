#include <bits/stdc++.h>

constexpr int MOD = 1e9 + 7;

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);

    int n, k, d;
    std::cin >> n >> k >> d;
    std::vector<std::vector<int>> mem(n+1, std::vector<int>(2, 0));
    mem[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= std::min(i, k); ++j) {
            if (j >= d) {
                mem[i][1] = (mem[i][1] + mem[i-j][0]) % MOD;
            } else {
                mem[i][0] = (mem[i][0] + mem[i-j][0]) % MOD;
            }
            mem[i][1] = (mem[i][1] + mem[i-j][1]) % MOD;
        }
    }
    std::cout << mem[n][1] << std::endl;

    return 0;
}
