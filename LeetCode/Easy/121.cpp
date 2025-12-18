class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int ans = 0, mn = 1e9;
        for (int price : prices) {
            ans = max(ans, price - mn);
            mn = min(mn, price);
        }
        return ans;
    }
};
