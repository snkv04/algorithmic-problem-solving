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
    - our operations are positive/negative INTEGERS, meaning that we can never scale down the magnitude of a subarray;
    we can only increase the magnitude and make it postiive or negative
        - why don't we ever need to use 0? first off, we'd only be able to have a single 0 in the final array; then,
        in any case where we'd need to use 0, we can replace that with a scaling of the suffix by a positive number
    - therefore, we only need to perform operations on prefixes and suffixes
    - now, just observe that since we want a strictly increasing array, if there are negative numbers at all, they'll
    be along a prefix; so, we can just brute-force over the size of the prefix, and use our greedy policy of scaling
    up/down prefixes/suffixes to ensure the decreasing magnitude of the negative portion and the increasing magnitude
    of the positive portion
    */

    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    vector<int> if_inc(n + 2, 0), if_dec(n + 2, 0);
    a.insert(a.begin(), -2e9);
    a.push_back(2e9);
    for (int i = 1; i <= n; ++i) {
        if (a[i] <= a[i - 1]) {
            if_inc[i - 1] = 1;
        }
    }
    for (int i = n; i >= 0; --i) if_inc[i] += if_inc[i + 1];
    a[0] = 2e9;
    a[n + 1] = -2e9;
    for (int i = n; i >= 1; --i) {
        if (a[i] <= a[i + 1]) {
            if_dec[i + 1] = 1;
        }
    }
    for (int i = 1; i <= n + 1; ++i) if_dec[i] += if_dec[i - 1];

    int ans = 1e9;
    for (int i = 0; i <= n; ++i) ans = min(ans, if_dec[i] + (i == 0 ? 0 : 1) + if_inc[i + 1]);
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
