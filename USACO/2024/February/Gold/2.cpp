#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
std::ostream& operator<<(std::ostream &os, const vector<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

int main() {
    /*
    summary of solution: for each bucket, it won't decrease until the next bucket that's strictly
    less than it. precompute these next buckets. then, for each bucket, jump through "next" values,
    and add these deltas to an array, whose prefix sum values will be the amount of milk on each day.
    however, that's too slow; a single "jump" between 2 buckets (meaning a drop in milk from the first
    bucket that occurs when reaching the second) might happen many times. so, we can find the number
    of times that jump will take place, and since those jumps will all take place on consecutive days,
    we can compute deltas of the deltas. run prefix sum operations to get the actual changes in milk
    per day, then run it again to get the real amount of milk per day.

    generalized ideas for the future:
    - if for each element A_i of an array A of length N we want to perform some operations on the
    window [i, i+N] where those windows wrap around cyclically, then check if it is possible to
    rotate the array such that the last operation needed (for any window starting at index i) happens
    at the last element and we never need to rotate after we hit the last element.
        - in this problem, this shifting is actually required. why? suppose we extend the array by
        its original length so that for each index 0<=i<N, we have at least N indices after it.
        if we say  that bucket B's next drop occurs at bucket C > B, and all buckets between A and B
        (where A <= B) end up at bucket B's amount of milk at the time of reaching bucket B, then not
        all of them will actually drop at C, because some of them might end their entire process at
        some bucket j, where B<=j<C. to avoid this situation, which we definitely want to avoid because
        it heavily complicates the simplification of just making all buckets in the interval [A, B]
        have their drop at C, we can just do the rotation (so then no bucket ever performs a drop after
        the last element of the size-N array), because then, we are guaranteed that all such triplets
        (A, B, C) are such that no buckets in the interval [A, B] are unable to reach C. they can all
        reach it, because C-A <= N-1, and the expiry of a bucket's process occurs N elements to the
        right of it.
        actually, i just realized that i'm wrong. the rotation does help, but it's not necessary.
        if we do the alternate solution, where we go with the monotonic stack from right to left,
        then this can be modified to handle the expiries of indices by using a deque instead of a
        queue. indices are updated at the right-end of the deque if they are too far to the right
        from the current index being processed.
    - if we do a weakly increasing monotonic stack from left to right, then for each element,
    we can determine the next element that is less than the current element. if we do a strictly
    increasing monotonic stack from right to left, then at the time of processing each element,
    the current stack is the "path" of next less elements all the way to the end of the array.
    - the outputs that we get from performing operations on indices (e.g., next[i] - i) might actually
    align perfectly with the indexing strategy assumed in the original problem (day 1 through day N),
    or it might not. literally, just don't worry about it and do whatever is most intuitive, and then
    change everything at the end.
    */

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int mn = 1e9; for (int ai : a) mn = min(ai, mn);
    int idx = -1; for (int i = 0; i < n; ++i) if (a[i] == mn) { idx = i; break; }
    rotate(a.begin(), a.begin() + ((idx + 1) % n), a.end());
    // cout << "a = " << a << endl;

    vector<int> next(n, -1); // next[i] = first index to right of i that's < a[i]
    stack<int> stk;
    for (int i = 0; i <= n; ++i) {
        int val = i == n ? 0 : a[i];
        while (stk.size() && a[stk.top()] > val) {
            next[stk.top()] = i;
            stk.pop();
        }
        stk.push(i);
    }
    // cout << "next = " << next << endl;

    /*
    for a given bucket, the only ones that will do the exact same jump as that bucket is the
    region of buckets to the left that are strictly greater than it. if we see a bucket to the
    left that's equal, then since we care about paths (going right) of strictly decreasing buckets,
    that bucket to the left that's equal won't use the current bucket as part of its path. that's
    why as soon as we see any bucket (prev[i]) that's <= the current bucket (i), we know that the
    range of buckets that will do the jump from i to next[i] will be [prev[i]+1, i].
    */
    vector<int> prev(n, -1); // prev[i] = first index to left of i that's <= a[i]
    stk = stack<int>();
    for (int i = n-1; i >= -1; --i) {
        int val = i >= 0 ? a[i] : 1;
        while (stk.size() && val <= a[stk.top()]) {
            prev[stk.top()] = i;
            stk.pop();
        }
        stk.push(i);
    }
    // cout << "prev = " << prev << endl;

    vector<ll> pref(n+1, 0);
    for (int i = 0; i < n; ++i) {
        if (next[i] == n) continue;

        int firsttime = next[i] - i;
        int numtimes = i - prev[i];
        // cout << "drop from " << make_pair(i, a[i]) << " to " << make_pair(next[i], a[next[i]]) << " starts on day " << firsttime << " and ends on day " << (firsttime + numtimes - 1) << endl;
        pref[firsttime] -= a[i] - a[next[i]];
        // if (firsttime + numtimes <= n)
            pref[firsttime + numtimes] += a[i] - a[next[i]];
        // cout << "after applying that delta, pref = " << pref << endl;
    }

    /*
    - start with deltas of deltas. do one accumulation to get true deltas, add initial value,
    then do another accumulation to get true values
    */
    for (int i = 1; i <= n; ++i) pref[i] += pref[i-1]; // accumulates deltas to get true reductions
    // cout << "after accumulating, pref = " << pref << endl;
    for (int i = 0; i < n; ++i) pref[0] += a[i]; // adds all the values to element 0
    // cout << "now, pref = " << pref << endl;
    for (int i = 1; i <= n; ++i) { // now, uses true reductions and the initial value to get true values
        pref[i] += pref[i-1];
        cout << pref[i] << '\n';
    }
    // cout << "final milk values on each day = " << pref << endl;
}
