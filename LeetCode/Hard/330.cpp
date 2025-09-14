class Solution {
public:
    int minPatches(vector<int>& coins, int target) {
        sort(coins.begin(), coins.end());

        unsigned long long ans = 0, maxpossible = 0;
        for (int coin : coins) {
            while (coin > maxpossible + 1 && maxpossible < target) {
                maxpossible = (2 * maxpossible) + 1;
                ++ans;
            }
            maxpossible += coin;

            if (maxpossible >= target) break;
        }

        while (maxpossible < target) {
            ++ans;
            maxpossible = (2 * maxpossible) + 1;
        }

        return ans;
    }
};
