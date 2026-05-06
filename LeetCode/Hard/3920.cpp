class Solution {
public:
    int maxFixedPoints(vector<int>& nums) {
        vector<pair<int, int>> shifts;
        for (int i = 0; i < nums.size(); ++i) {
            if (i < nums[i]) continue;

            shifts.push_back(make_pair(i - nums[i], nums[i]));
        }
        sort(shifts.begin(), shifts.end());

        vector<int> lis;
        for (auto [shift, num] : shifts) {
            if (lis.empty() || lis.back() < num) {
                lis.push_back(num);
            } else {
                int l = 0, r = lis.size() - 1, idx = -1;
                while (l <= r) {
                    int m = (l + r) / 2;
                    if (lis[m] >= num) {
                        idx = m;
                        r = m - 1;
                    } else {
                        l = m + 1;
                    }
                }
                lis[idx] = num;
            }
        }
        return lis.size();
    }
};
