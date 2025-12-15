class Solution {
public:
    long long getDescentPeriods(vector<int>& prices) {
        long long ans = 0, curr = 0;
        for (int i = 0; i < prices.size(); ++i) {
            if (i == 0 || prices[i] != prices[i-1] - 1) {
                curr = 1;
            } else {
                curr += 1;
            }
            ans += curr;
        }
        return ans;
    }
};
