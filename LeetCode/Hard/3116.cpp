class Solution {
private:
    long long gcd(long long a, long long b) {
        long long A = max(a, b), B = min(a, b);
        while (B != 0) {
            long long R = A % B;
            A = B;
            B = R;
        }
        return A;
    }

    long long lcm(long long a, long long b) {
        return a * b / gcd(a, b);
    }

    long long num_can_make(long long num, vector<int> &coins) {
        long long num_leq = 0;
        for (int mask = 1; mask < (1 << coins.size()); ++mask) {
            long long multiple = 1;
            int num_diff_coins = __builtin_popcount(mask);
            for (int j = 0; j < coins.size(); ++j) {
                if ((1 << j) & mask) {
                    multiple = lcm(multiple, coins[j]);
                }
            }

            long long num_multiples = num / multiple;
            if (num_diff_coins % 2) {
                num_leq += num_multiples;
            } else {
                num_leq -= num_multiples;
            }
        }
        return num_leq;
    }

public:
    long long findKthSmallest(vector<int>& coins, int k) {
        /*
        we can use binary search to find the minimum element such that
        there are at least k elements of that combined sequence leq
        the checked element. however, how can we see how many elements from
        that combined sequence are less than or equal to some given number?
        well, we use the inclusion-exclusion principle. how? note that the
        reason we can't just separately check the number of multiples of each
        coin less than or equal to some element is that some of those multiples
        are shared between different coins. what to do then? note that the
        sequence of possible amounts that can be made is the union of the
        multiples of each coin. we are trying to find out how much of this union
        is leq some element. once we know that our goal is to find the
        cardinality of the union of some sets, we can directly use
        inclusion-exclusion. find all the multiples corresponding to
        intersections of any size, where the intersection of multiples for
        coins C1, C2, and C3 would be the number of times that lcm(C1, C2, C3)
        can fit into the checked element. now, to be clear, we iterate
        over all possible subsets directly and then find out the size of the
        intersection (as its parity depends on whether the cardinality of that
        intersection set is subtracted or added), instead of trying to find all
        2-intersections, 3-intersections, etc. in order.
        */

        long long l = 1, r = static_cast<long long>(1e18), ans = -1;
        while (l <= r) {
            long long mid = l + (r - l) / 2;
            if (num_can_make(mid, coins) >= k) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        return ans;
    }
};
