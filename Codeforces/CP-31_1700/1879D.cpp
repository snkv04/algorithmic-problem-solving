#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = 998244353;
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
    - first off, if we are to decompose each number into separate bits and compute the answer separately
    for each bit (making sure to multiply the answer for each bit k by 2^k), then note that the XOR of
    any number of bits can either be 0 or 1. so, for any given segment [l, r], the XOR sum of that segment
    will either be 0 or 1. if we multiply that by the length r-l+1 for every segment [l, r], then the output
    of that product will either be 0 or simply the length itself, r-l+1.
    - alright, so now what we are basically doing is finding the length of every segment whose XOR sum is
    1 and summing them up. we can further break down this case (of the XOR sum being 1) into 2 cases. for
    a given right bound r, the XOR prefix sum ending at index r will either be 1 or 0. what we are looking
    for is all possible left bounds l such that the sum between l and r is 1, meaning that the prefix
    sum up to l and up to r are not the same (one is 0 and the other is 1).
    - a major reason why this is easy to compute is that, for each r, we don't actually have to search across
    all prefixes from 0 to r-1 and see which of them are different from pref[r]. we can speed this up by keeping
    track of, for each of the two possible states (pref[l] == 0 and pref[l] == 1), how many prefixes are in
    each and also the sum of (-l+1) for all of those. the second part is because we can separate the expression
    (r-l+1) into two parts, one that is computed at the time of passing the left bound and one that is computed
    at the time of passing the right bound. in summary, the thing that speeds up the "searching over all previous
    indices" is that the number of states for each of those previous indices is limited (0 or 1 for prefix XOR
    sum) and that when at index r we just care about all the previous indices l that fall in one of those states,
    so we can just keep track of running sums for each of those states (in this case, just 2). it's like placing
    each index in a bucket so that later we can look at whichever bucket we need.

    generalizable ideas:
    - note that the XORs are either 0 or 1 for each bit separately, which simplifies what the "product between
    xor and length" really means (it's basically either the length or 0)
    - when doing the thing where, for each index, we are looking across previous indices to see which ones
    match a condition, we can instead place each index into a bucket based on which condition it satisfies
    (or which "state" it's in), and then for each index, we can simply look in the bucket corresponding to
    the state we care about for previous indices
    - when we separate out the "r" and "l-1" parts into things that are computed separately, note that the
    "index_sums" are used for computing the sum over all "l-1" terms that we care about, and the "index_counts"
    are used for knowing how many times there have been such "l-1" terms so that we can properly multiply "r"
    by that number of times; intuitively, we want the number of l-1 terms to match the number of r terms when
    we are iterating over r, so we keep track of the counts of l-1 terms in order to make the computation of
    the "r" part ALIGN with the other part. in short, we need both just so that we can compute the sum of
    left borders and sum of right borders properly.
    */

    int n;
    cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    ll ans = 0;
    for (int b = 0; b < 30; ++b) {
        ll bit_ans = 0;
        vector<int> pref(n+1, 0);
        for (int i = 0; i < n; ++i) {
            int bit = (a[i] & (1 << b)) > 0;
            pref[i+1] = pref[i] ^ bit;
        }

        vector<ll> index_sums(2, 0), index_counts(2, 0);
        // index_sums[0] = 0;
        index_counts[0] = 1;
        for (int i = 1; i <= n; ++i) {
            int prefix_xor = pref[i];
            bit_ans = (bit_ans + (index_counts[1 - prefix_xor] * i - index_sums[1 - prefix_xor])) % MOD;
            ++index_counts[prefix_xor];
            index_sums[prefix_xor] += i;
        }

        ans = (ans + (bit_ans * (1LL << b))) % MOD;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
