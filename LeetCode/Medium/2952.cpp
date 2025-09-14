/*
ideas involved:
- for a given coin value, that coin cannot be helpful for making sums less
than that coin's value
- if we can make all sums from 1 to x, inclusive, and we have a coin of value y, then we can now make all sums from 1 to x+y
- we iterate from lower to higher sums, because coins will impact sums that
are >= the coin value. if we were to iterate in descending order, then for a
given sum, you haven't processed the coins that could make that sum.
- you only add a coin when it is necessary to make a sum, for which all previous
coins that you looked at couldn't make (and all future coins wouldn't be able
to, because the sum is too low)
- we sort the coins. why? because then, for a given coin value, you've already
seen any possible ways you could make that sum or nearby sums with smaller
coins. put simply, we process coins from smaller values to larger values
because we want to process sums from smaller values to larger values, and with
each coin comes new sums we can make.
- we don't actually iterate over the sums, by the way, but the coins. why? each coin opens up a range of sums that are obtainable. it is easier to process a
bunch of sums at once than to process, for a given sum, how to make it?
*/

class Solution {
public:
    int minimumAddedCoins(vector<int>& coins, int target) {
        sort(coins.begin(), coins.end());

        unsigned long long ans = 0, maxpossible = 0;
        for (int coin : coins) {
            while (coin > maxpossible + 1) {
                maxpossible = (2 * maxpossible) + 1;
                ++ans;
            }
            maxpossible += coin;
        }

        while (maxpossible < target) {
            ++ans;
            maxpossible = (2 * maxpossible) + 1;
        }

        return ans;
    }
};
