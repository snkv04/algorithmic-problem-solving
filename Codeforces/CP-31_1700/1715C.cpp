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
        - for a given subarray, we care about the number of "split" points in the subarray
        - find the sum of that quantity across all subarrays
    - solution:
        - instead of looking across all subarrays and adding the number of split points from each,
        we can look at all split points and add the number of subarrays it appears in
        - then, the queries can be handled easily, because they only modify at most 2 split points each
    - details:
        - think of a split point as an indicator variable; it helps conceptually for the
        mathematical notation, as indicator variables always do!
        - a split point involves the array elements to both sides of it
        - this sum rearrangement is a classic technique; in particular, it is helpful because by rearranging
        the sum, we make the new inner sum easy to compute.
    */

    // reads in input
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    cin >> a;

    // computes all the initial split points
    ll ans = 1LL * n * (n+1) / 2;
    vector<ll> b(n-1, 0);
    for (int i = 0; i < n-1; ++i) {
        if (a[i] != a[i+1]) {
            b[i] = 1;
            ans += 1LL * (i+1) * (n-i-1);
        }
    }

    // handles each query
    auto in_bounds = [&](int idx) { return idx >= 0 && idx < n; };
    while (m--) {
        // reads in the query
        int i, x;
        cin >> i >> x;
        --i;

        // removes previous contributions
        for (int j = i-1; j <= i; ++j) {  // only 2 values
            if (in_bounds(j) && in_bounds(j+1)) {
                ans -= b[j] * (j+1) * (n-j-1);
            }
        }

        // updates a[] and b[], and then adds new contributions
        a[i] = x;
        for (int j = i-1; j <= i; ++j) {
            if (in_bounds(j) && in_bounds(j+1)) {
                b[j] = a[j] != a[j+1];
                ans += b[j] * (j+1) * (n-j-1);
            }
        }
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
