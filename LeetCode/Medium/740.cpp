class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        vector<int> copy = nums;
        sort(copy.begin(), copy.end());
        vector<pair<long long, long long>> pairs;
        for (int i = 0; i < copy.size(); ++i) {
            if (i == 0 || copy[i] != copy[i-1]) {
                pairs.push_back(make_pair(copy[i], 1));
            } else {
                pairs.back().second += 1;
            }
        }

        int n = pairs.size();
        vector<long long> mem(n, 0);
        int ptr = 0;
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            while (ptr + 1 < n && pairs[ptr].first < pairs[i].first - 1) {
                ++ptr;
            }

            mem[i] = max(
                (i == 0 ? 0 : mem[i-1]),
                pairs[i].first * pairs[i].second + (
                    ptr == 0 ? 0 : mem[ptr - 1]
                )
            );
            ans = max(ans, mem[i]);
        }
        return ans;
    }
};
