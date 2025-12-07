#include <bits/stdc++.h>

struct RollingHash {
    RollingHash(std::string &str) : str(str), n(str.size()) {
        _build_hashes();
        _build_powers();
    }

    // left and right are both 0-based indices, where left is inclusive and right is exclusive
    std::pair<long long, long long> get_hash(int left, int right) {
        std::array<long long, 2> result;
        for (int field = 0; field < 2; ++field) {
            result[field] = (rolling[field][right] - (
                rolling[field][left] * PRIME_POWERS[field][right - left] % MOD[field]
            ) + MOD[field]) % MOD[field];
        }
        return std::make_pair(result[0], result[1]);
    }

private:
    std::vector<long long> PRIMES = {998244353, 999999937}, MOD = {1000000007, 1000000009};
    std::vector<std::vector<long long>> PRIME_POWERS, rolling;
    std::string str;
    int n;

    void _build_hashes() {
        rolling = std::vector<std::vector<long long>>(2, std::vector<long long>(n + 1, 0));
        for (int field = 0; field < 2; ++field) {
            for (int i = 1; i <= n; ++i) {
                int letter_as_int = str[i - 1];
                rolling[field][i] = (rolling[field][i - 1] * PRIMES[field] + letter_as_int) % MOD[field];
            }
        }
    }

    void _build_powers() {
        PRIME_POWERS = std::vector<std::vector<long long>>(2, std::vector<long long>(n + 1, 1));
        for (int field = 0; field < 2; ++field) {
            for (int i = 1; i <= n; ++i) {
                PRIME_POWERS[field][i] = (PRIME_POWERS[field][i - 1] * PRIMES[field]) % MOD[field];
            }
        }
    }
};
