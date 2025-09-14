/*
[1, 3] -> 1
[4, 15] -> 2
[16, 63] -> 3
[64, 255] -> 4
...
*/

class Solution {
public:
    long long minOperations(vector<vector<int>>& queries) {
        map<long long, long long> to_ops;
        unordered_map<long long, long long> pow;
        long long power = 4, exp = 1;
        while (power < 2e9) {
            to_ops[power - 1] = exp; // 3->1, 15->2, etc.
            pow[exp] = power;
            power *= 4;
            ++exp;
        }

        long long ans = 0;
        for (vector<int> &query : queries) {
            long long l = query[0], r = query[1];
            auto left_upper = to_ops.lower_bound(l),
                right_upper = to_ops.lower_bound(r);
            
            if (left_upper == right_upper) {
                long long ops = (r - l + 1) * left_upper->second;
                ans += (ops + 1) / 2;
            } else {
                long long ops = (
                    (left_upper->first + 1 - l) * left_upper->second +
                    (r - ((right_upper->first + 1) / 4) + 1) * right_upper->second
                );

                for (
                    long long num_ops = left_upper->second + 1;
                    num_ops <= right_upper->second - 1;
                    ++num_ops
                ) {
                    long long high = pow[num_ops], low = pow[num_ops - 1];
                    ops += (high - low) * num_ops;
                }

                ans += (ops + 1) / 2;
            }
        }
        return ans;
    }
};
