class Solution {
public:
    int maxValue(vector<int>& nums1, vector<int>& nums0) {
        int ones = 0, zeros = 0;
        vector<pair<int, int>> segments;
        int n = nums0.size();
        for (int i = 0; i < n; ++i) {
            if (nums0[i] == 0) {
                ones += nums1[i];
            } else if (nums1[i] == 0) {
                zeros += nums0[i];
            } else {
                segments.push_back(make_pair(nums1[i], nums0[i]));
            }
        }
        sort(
            segments.begin(),
            segments.end(),
            [](const pair<int, int> &a, const pair<int, int> &b) {
                if (a.first != b.first) {
                    return a.first > b.first;
                } else {
                    return a.second < b.second;
                }
            }
        );

        long long ans = 0, place = 1;
        constexpr int MOD = 1e9 + 7;
        for (int i = 0; i < zeros; ++i) {
            place = (place * 2) % MOD;
        }
        for (int i = segments.size() - 1; i >= 0; --i) {
            for (int j = 0; j < segments[i].second; ++j) {
                place = (place * 2) % MOD;
            }
            for (int j = 0; j < segments[i].first; ++j) {
                ans = (ans + place) % MOD;
                place = (place * 2) % MOD;
            }
        }
        for (int i = 0; i < ones; ++i) {
            ans = (ans + place) % MOD;
            place = (place * 2) % MOD;
        }
        return ans;
    }
};
