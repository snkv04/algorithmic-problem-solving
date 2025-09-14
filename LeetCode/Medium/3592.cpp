class Solution {
public:
    vector<int> findCoins(vector<int>& numWays) {
        vector<int> newNumWays(numWays);
        newNumWays.insert(newNumWays.begin(), 0);
        int n = numWays.size();
        vector<int> coins;
        vector<int> resultingWays(n+1, 0);
        resultingWays[0] = 1;
        for (int coin = 1; coin <= n; ++coin) {
            int ways = newNumWays[coin];
            if (ways > resultingWays[coin]) {
                coins.push_back(coin);
                for (int i = coin; i <= n; ++i) {
                    resultingWays[i] += resultingWays[i-coin];
                }
            }

            if (resultingWays[coin] != ways) {
                return vector<int>();
            }
        }
        return coins;
    }
};
