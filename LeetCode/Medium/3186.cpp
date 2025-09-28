class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        /*
        generalizable ideas:
        - if dealing with multiple numbers that are equal, which can cause
        a long string of non-distinct, contiguous elements within the sorted
        version of the array, then just replace it with an array of pairs, where
        the first value is the element's actual value and the second value
        is the frequency of that element in the array. this could be especially
        useful for problems like this that require a sliding window or
        two pointer algorithm
        - if we have some sort of sliding window that makes it so that if we
        "count" the current element then we can't count count previous elements
        within some range (whether by value, like we can't count any elements
        a[j] such that j < i and a[j] >= a[i] - 2, or by index, like we can't
        count any elements a[j] such that j < i and j >= i - 2), then the same
        restriction is automatically applied to "next" elements. with hindsight,
        this is obvious. additionally, even if the restriction was uneven (like
        for a given element a[i], if we use it, then we can't use a[i-1],
        a[i-2], and a[i+1]), then even in that case, we can't use element a[i+2]
        since when the index i moves to i+2, then the "lookback" restriction
        will stop that from happening even though it was fine under the
        "lookforward" restriction (basically, the restriction on which
        neighboring elements can be used is symmetric). in such an uneven case,
        the larger restriction would apply in both directions.
        */

        vector<int> copy = power;
        sort(copy.begin(), copy.end());
        vector<pair<long long, long long>> pairs;
        for (int i = 0; i < copy.size(); ++i) {
            if (i == 0 || copy[i] != copy[i-1]) {
                pairs.push_back(make_pair(copy[i], 1));
            } else {
                pairs.back().second += 1;
            }
        }

        //           ptr             i
        // [(1, 1), (2, 1), (3, 1), (4, 1), (5, 1)]
        int n = pairs.size();
        vector<long long> mem(n, 0);
        int ptr = 0;
        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            while (ptr + 1 < n && pairs[ptr].first < pairs[i].first - 2) {
                ++ptr;
            }

            // mem[i] is the best amount of power (summed) only considering
            // the first (i+1) pairs
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
