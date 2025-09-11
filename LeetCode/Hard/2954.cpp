class Solution {
private:
    const int MOD = 1e9 + 7;

    long long pow(long long base, long long exp) {
        if (exp == 0) return 1;

        long long result = pow(base, exp / 2);
        result = (result * result) % MOD;
        if (exp % 2) {
            result = (result * base) % MOD;
        }
        return result;
    }

    long long inv(long long x) {
        return pow(x, MOD - 2);
    }

    long long div(long long num, long long denom) {
        return (num * inv(denom)) % MOD;
    }

public:
    int numberOfSequence(int n, vector<int>& sick) {
        // precompute factorials and powers of 2
        vector<long long> factorial(n + 1), exp(n+1);
        factorial[0] = 1;
        for (int i = 1; i <= n; ++i) {
            factorial[i] = (factorial[i-1] * i) % MOD;
        }
        exp[0] = 1;
        for (int i = 1; i <= n; ++i) {
            exp[i] = (exp[i-1] * 2) % MOD;
        }

        // make sick people easily checkable
        vector<bool> is_sick(n, false);
        for (int sick_person : sick) is_sick[sick_person] = true;

        // gather all segments of non-sick people and compute number of ways
        // to order each segment
        int last_sick = -1;
        vector<pair<int, long long>> segments;  // first is length, second is num ways
        for (int i = 0; i < n; ++i) {
            if (!is_sick[i]) {
                if (i == n-1 || is_sick[i+1]) {
                    int dist = i - last_sick;
                    if (dist) {
                        if (last_sick == -1 || i == n-1) {
                            segments.push_back(make_pair(dist, 1));
                        } else {
                            segments.push_back(make_pair(dist, exp[dist-1]));
                        }
                    }
                }
            } else {
                last_sick = i;
            }
        }

        // multiply number of ways to order each segment, then multiply by
        // the number of ways to distribute the indices in the infection order
        // across segments
        long long ans = 1, numerator = 0, denominator = 1;
        for (const pair<int, long long> &segment : segments) {
            ans = (ans * segment.second) % MOD;
            numerator += segment.first;
            denominator = (denominator * factorial[segment.first]) % MOD;
        }
        numerator = factorial[numerator];
        ans = (ans * div(numerator, denominator)) % MOD;
        return ans;
    }
};
