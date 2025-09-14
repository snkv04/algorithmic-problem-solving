using ll = long long;

struct SegmentTree {
private:
    int n;
    vector<int> t;

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2*v, l, m, idx, val);
        } else {
            _update(2*v+1, m+1, r, idx, val);
        }
        t[v] = t[2*v] + t[2*v+1];
    }

    int _query(int v, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return t[v];
        }
        if (r < ql || qr < l) {
            return 0;
        }

        int m = l + (r - l) / 2;
        return (
            _query(2*v, l, m, ql, qr)
            + _query(2*v+1, m+1, r, ql, qr)
        );
    }

public:
    SegmentTree(int n) {
        this->n = n;
        t.resize(4*n);
        fill(t.begin(), t.end(), 0);
    }

    void update(int idx, int val) {
        _update(1, 0, n-1, idx, val);
    }

    int query(int ql, int qr) {
        return _query(1, 0, n-1, ql, qr);
    }
};

class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        /*
        - the problem is asking how many subarrays have their sum within
        the inclusive range [lower, upper]
        - this is equivalent to asking how many pairs (l, r) are such that the
        sum of the elements in the inclusive range [l, r] is within the
        inclusive range [lower, upper]
        - this is equivalent to asking how many pairs (l, r) are such that
        the prefix sum ending at r minus the prefix sum ending at l-1 is
        within the inclusive range [lower, upper]
        - we do not want to iterate through l from left to right and find
        out how many r are to the right such that pref[r]-pref[l] is within
        the range. that would be correct, but it is too slow
        - instead, we can directly iterate through the prefix sums, keeping
        a sliding window through them such that the length of the sliding
        window is constrained by making sure that (diff between current
        prefsum and right of window is >= lower) and that (diff between current
        prefsum and left of window is <= upper). this makes the order of 
        iteration for the prefix sums into their sorted order, as that is easier
        - then, what we have on each iteration of the for loop is a single
        right-side index and a range of possible left-side indices, which are
        consecutive in sorted order but might be scattered across the array when
        we map back to the original indices that they are prefix sums for. they
        might also be to the right of the right-side index.
        - so, to only count the selections that are strictly to the left of this
        right-side index, we can use a segment tree.
        - that's all.

        generalizable ideas:
        - when counting the number of pairs (i, j) that satisfy some condition,
        we can iterate through j in increasing (or any) order and count the
        number of i less than (or, less than or equal to) that j that satisfy
        the condition. we could also iterate through j and count all i that
        satisfy the condition (so i might be < j or > j), and then divide
        that count by 2, since each pair would get counted twice
        - when keeping a sliding window, you don't always have to move the
        r-index by 1 and then move the l-index by a variable amount (or the
        opposite, where you iterate through l and move r based on some 
        constraint). you can instead iterate i through the array, and for
        each i, move both l and r based on constraining their relation to i
        - instead of iterating through the prefix sums from left to right,
        and coutning the prefix sums to the left whose difference is within
        the required range, we can iterate through the prefix sums in any order,
        only consider the prefix sums whose difference is within the required
        range, and then count the ones to the left. we only end up iterating
        through the prefix sums in sorted order (and mapping back to the
        original indices) because this makes it easier to enforce the sliding
        window. this is still fine, though, as the segment tree makes it easy
        to count the valid "left" indices that are actually to the left. put
        simply, we are swapping the order in which we impose the constraints,
        where the two constraints are "is to the left" and "is within the
        window"

        other ideas, and why they do or don't work:
        - we could brute force all possible subarrays and compute the range
        sum each time. that is O(n^3), which is too slow
        - a reasonable place to start: we could brute force all possible
        subarrays and compute the range sum using prefix sums, but this is
        O(n^2), which is too slow
        - sort the prefix sums, and then iterate through each of them. for each,
        assume that that is the right end, and keep a sliding window of which
        prefix sums could be used as the left end, regardless of if the "left"
        is actually to the left of the right in the array. the reason this
        doesn't work is because p[r]-p[l] is the ACTUAL sum of the subarray
        that goes from (l-1) to r, inclusive, while p[l]-p[r] is the flipped
        sum. so, if lower != -upper, then this logic just straightforwardly
        doesn't apply. if we want p[r]-p[l] to be within [lower, upper] while
        also representing a valid subarray sum, then l must be <= r.
        */

        int n = nums.size();
        vector<ll> prefsums(n+1, 0);
        for (int i = 1; i <= n; ++i) {
            prefsums[i] = prefsums[i-1] + nums[i-1];
        }

        vector<pair<ll, ll>> sorted;
        for (int i = 0; i <= n; ++i)
            sorted.push_back(make_pair(i, prefsums[i]));
        sort(
            sorted.begin(),
            sorted.end(),
            [](const pair<ll, ll> &p1, const pair<ll, ll> &p2) {
                if (p1.second != p2.second) {
                    return p1.second < p2.second;
                } else {
                    return p1.first < p2.first;
                }
            }
        );

        int l = 0, r = 0;
        int ans = 0;
        SegmentTree st(n+1);
        for (const pair<ll, ll> p : sorted) {
            if (p.first == 0) continue; // skip when right is before all elems

            ll right = p.second;
            while (r <= n && right - sorted[r].second >= lower) {
                st.update(sorted[r++].first, 1);
            }
            while (l <= n && right - sorted[l].second > upper) {
                st.update(sorted[l++].first, 0);
            }

            ans += st.query(0, p.first - 1);
        }
        return ans;
    }
};
