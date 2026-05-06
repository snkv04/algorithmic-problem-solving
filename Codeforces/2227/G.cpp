#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream &os, const std::array<T, N> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        is >> v[i];
    }
    return is;
}

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
    }
    return is;
}

ll gcd(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    ll A = max(a, b), B = min(a, b);
    while (B != 0) {
        ll R = A % B;
        A = B;
        B = R;
    }
    return A;
}

ll lcm(ll a, ll b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    return a / gcd(a, b) * b;
}

struct SegmentTree {
    SegmentTree(int n) : n(n) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
    }

    SegmentTree(const std::vector<int> &arr) : arr(arr), n(arr.size()) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int vertex, int left, int right) {
        if (left == right) {
            tree[vertex] = arr[left];
            return;
        }

        int mid = left + (right - left) / 2;
        build(2 * vertex, left, mid);
        build(2 * vertex + 1, mid + 1, right);
        tree[vertex] = tree[2 * vertex] + tree[2 * vertex + 1];
    }

    long long _query(int vertex, int left, int right, int query_left, int query_right) {
        if (right < query_left || query_right < left) {
            return 0;
        }
        if (query_left <= left && right <= query_right) {
            return tree[vertex];
        }

        int mid = left + (right - left) / 2;
        return _query(2 * vertex, left, mid, query_left, query_right) +
            _query(2 * vertex + 1, mid + 1, right, query_left, query_right);
    }

    long long query(int left, int right) {
        return _query(1, 0, n - 1, left, right);
    }

    void _update(int vertex, int left, int right, int idx, long long val) {
        if (left == right) {
            tree[vertex] = val;
            return;
        }

        int mid = left + (right - left) / 2;
        if (idx <= mid) {
            _update(2 * vertex, left, mid, idx, val);
        } else {
            _update(2 * vertex + 1, mid + 1, right, idx, val);
        }
        tree[vertex] = tree[2 * vertex] + tree[2 * vertex + 1];
    }

    void update(int idx, long long val) {
        _update(1, 0, n - 1, idx, val);
    }

private:
    int n;
    std::vector<long long> tree;
    std::vector<int> arr;
};

void solve() {
    /*
    - problem pattern:
        - given an array A, you can perform operations on it called O
        - an array A is called valid if you can start at a state S (the initial state) and reach a
        target state T by only using operations of type O
        - count the number of subarrays that are valid
    - solution:
        - identify an invariant of the operation: what doesn't change every time you perform O?
        - using that invariant, come up with a more clever strategy of classifying whether we can move
        an array/subarray from S to T (specifically, more clever than brute-forcing all sequences
        of operations)
        - using that easy classification strategy, come up with a way to quickly count such valid subarrays,
        such as iterating over R and counting the number of valid L that satisfy L <= R
    */

    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    vector<ll> alt_pref(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        alt_pref[i] = alt_pref[i - 1] + ((i % 2) ? 1 : -1) * a[i - 1];
    }
    vector<pair<int, ll>> sorted;
    for (int i = 0; i <= n; ++i) sorted.push_back(make_pair(i, alt_pref[i]));

    // - activate indices in increasing order of prefix sum
    // - for an odd index, we want to see the number of even-indexed prefix sums less than it to the left
    // - activate index if even, query index if odd
    ll ans = 0;
    sort(sorted.begin(), sorted.end(), [](const pair<int, ll> &a, const pair<int, ll> &b) {
        if (a.second != b.second) {
            return a.second < b.second;
        } else {
            return a.first > b.first;
        }
    });
    SegmentTree st(n + 1);
    for (auto [idx, pref] : sorted) {
        if (idx % 2) {
            ans += st.query(0, idx);
        } else {
            st.update(idx, 1);
        }
    }

    // - activate indices in decreasing order of prefix sum
    // - for an even index, we want to see the number of odd-indexed prefix sums greater than it to the left
    // - activate index if odd, query index if even
    sort(sorted.begin(), sorted.end(), [](const pair<int, ll> &a, const pair<int, ll> &b) {
        if (a.second != b.second) {
            return a.second > b.second;
        } else {
            return a.first > b.first;
        }
    });
    st = SegmentTree(n + 1);
    for (auto [idx, pref] : sorted) {
        if (idx % 2) {
            st.update(idx, 1);
        } else {
            ans += st.query(0, idx);
        }
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
