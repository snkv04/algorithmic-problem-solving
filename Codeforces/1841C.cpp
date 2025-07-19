#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return _query(2 * v, l, m, ql, qr)
            + _query(2 * v + 1, m + 1, r, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }
};

void solve() {
    /*
    - first, start with the brute force solution
        - reverse the string
        - for each index, for each value, change that index to that value
        - then, find out the sum. how?
        - iterate from left to right, and for each, keep track of the max seen so far.
        - for a given index, if the value is strictly less than the max, subtract, otherwise, add
    - what pieces of information are important?
        - the index we're at, so we know what the original value was at that index
        - at a given index, you have the option of either changing it or not changing it
        - at a given index, the determination of whether it gets added or subtracted depends on
        the max seen so far
    - so, for a given prefix, we can find (across all 5 values that that index can take) what are
    the maximum possible sums if it has or hasn't been changed, and if the maximum seen so far is
    1, 2, 3, 4, or 5
    - for each index, we can just iterate through the value to "change" it to and what was the
    maximum previous seen so far for the previous index, and then from that, the maximum previous
    seen so far for the current index AS WELL AS whether or not we have done a change on the current
    index can easily be determined.

    what can be generalized?
    - always start with the brute force solution, see what pieces of information are important
    and what things are just recomputed over and over again, and then write a DP solution that
    reuses the recomputed parts
    - when you're iterating through values for the directly previous index, there might be a variable
    that corresponds to that directly previous index (in this case, it's what you changed that
    value to) and a variable that corresponds to all previous indices (in this case, it's what
    the maximum value seen so far is). in general, you want to iterate over the latter, even if
    you're iterating over the former for the current index
    - when deciding what to construct a DP state from, consider what pieces of information are
    important from the previous state/states. in this problem, the stuff that is useful to know
    from the previous states is whether or not there has been a change and what the maximum seen
    was. the thing that we are iterating over on the current state is what to change the current
    value to. that is exactly what happens in the DP solution! based on that information, we construct
    the list of states for the current element as (what was max seen so far, was there a change or no).
    then, we can look at all possible values for the current element. for each, we can find a few
    pieces of information: if the value we're looking at is different from its original, then we
    are changing the current element (and we can't have changed something previously). if the
    value we're looking at is the same, then either nothing has changed at all or something has
    changed previously. for each of these 3 cases (current is same and 0 total changes, current
    is same and 1 total changes, current is different and 1 total changes), we iterate through all
    possible max seen so far values for the previous element, and update the memoized result at the
    DP state where the max seen so far for the current element can easily be found.
        - basically: figure out brute force solution. identify what pieces of information are even
        important from past states and define the state using that. iterate over all values of current
        element just like in brute force solution. each of those states has its own cases. for each
        possible case, which we can literally write separately in the code for simplicity, iterate
        through all ways to step into that state from any previous states and update the memoized
        result for that state.
    */

    string s;
    cin >> s;
    reverse(s.begin(), s.end());
    int n = s.size();
    vector<int> a(n, 0);
    for (int i = 0; i < n; ++i) {
        a[i] = (int) (s[i] - 'A');
    }

    map<int, int> idx_to_val;
    int acc = 1;
    for (int i = 0; i < 5; ++i) {
        idx_to_val[i] = acc;
        acc *= 10;
    }

    vector<vector<vector<ll>>> mem(n+1, vector<vector<ll>>(5, vector<ll>(2, -1e18)));
    mem[0][0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 5; ++j) { // iterating over possible value for current index
            if (j == a[i-1]) {
                // the current value is unchanged

                // assume we have had no changes so far
                for (int k = 0; k < 5; ++k) { // iterating over maxseen for previous index
                    ll adding = ((j < k) ? -1 : 1) * idx_to_val[j];
                    mem[i][max(j, k)][0] = max(mem[i][max(j, k)][0], mem[i-1][k][0] + adding);
                }

                // assume we have had a change in a previous index
                for (int k = 0; k < 5; ++k) {
                    ll adding = ((j < k) ? -1 : 1) * idx_to_val[j];
                    mem[i][max(j, k)][1] = max(mem[i][max(j, k)][1], mem[i-1][k][1] + adding);
                }
            } else {
                // the current value is changed
                for (int k = 0; k < 5; ++k) {
                    ll adding = ((j < k) ? -1 : 1) * idx_to_val[j];
                    mem[i][max(j, k)][1] = max(mem[i][max(j, k)][1], mem[i-1][k][0] + adding);
                }
            }
        }
    }

    ll ans = -1e18;
    for (int k = 0; k < 5; ++k) {
        for (int changed = 0; changed < 2; ++changed) {
            ans = max(ans, mem[n][k][changed]);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
