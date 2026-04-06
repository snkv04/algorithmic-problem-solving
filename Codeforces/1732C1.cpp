#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
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

void solve() {
    /*
    - problem:
        - across all subsegments (l, r), find the maximum value of
        sum(a[l], a[l+1], ..., a[r]) - xor(a[l], a[l+1], ..., a[r])
        - if there are multiple, then give any such subarray with the shortest length
    - solution:
        - first off, we cannot use Kadane's, because the greedy splitting logic doesn't work
        - however, we can notice that for a fixed segment, then our function value will always
        be monotonically weakly increasing if we append an element on either side
        - so, clearly, the maximum function value is achieved over the whole array, and the hard
        part is finding a short segment for that value
        - to do this, instead of iterating over all pairs (l, r), we can iterate over each l, and
        find the minimum r such that f(l, r) == f(1, n) using binary search
    */

    // reads in input
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;
    int l, r;
    cin >> l >> r;

    // precomputes prefix sums and prefix XOR sums
    vector<ll> pref_sum(n), pref_xor(n);
    for (int i = 0; i < n; ++i) {
        pref_sum[i] = (i == 0 ? 0 : pref_sum[i - 1]) + a[i];
        pref_xor[i] = (i == 0 ? 0 : pref_xor[i - 1]) ^ a[i];
    }

    // finds min-length segment
    ll ans = pref_sum[n - 1] - pref_xor[n - 1];
    ll ans_l = 0, ans_r = n - 1;
    for (int i = 0; i < n; ++i) {
        // finds a value of r (idx) for the current value of l (i)
        int l = i, r = n - 1, idx = -1;
        while (l <= r) {
            int m = (l + r) / 2;
            ll val = (pref_sum[m] - (i == 0 ? 0 : pref_sum[i - 1])) -
                     (pref_xor[m] ^ (i == 0 ? 0 : pref_xor[i - 1]));
            if (val == ans) {
                idx = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }

        // checks if it's the shortest segment
        if (idx != -1 && idx - i < ans_r - ans_l) {
            ans_l = i;
            ans_r = idx;
        }
    }
    cout << ans_l + 1 << ' ' << ans_r + 1 << '\n';
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
