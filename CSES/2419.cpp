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
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    // "cnt" refers to "count of powers of 2"
    vector<int> cnt_in_num(n, 0);
    for (int i = 2; i < n; ++i) {
        int copy = i;
        while (copy % 2 == 0) {
            copy /= 2;
            cnt_in_num[i] += 1;
        }
    }

    vector<int> cnt_in_factorial(n, 0);
    for (int i = 2; i < n; ++i) {
        cnt_in_factorial[i] = cnt_in_factorial[i - 1] + cnt_in_num[i];
    }

    // parity_of_nm1Cr[i] = parity of nCr(n - 1, i)
    vector<int> parity_of_nm1Cr(n, 1);  // default to odd
    for (int i = 0; i < n; ++i) {
        int cnt_in_num = cnt_in_factorial[n - 1];
        int cnt_in_denom = cnt_in_factorial[i] + cnt_in_factorial[n - 1 - i];
        if (cnt_in_num > cnt_in_denom) {
            parity_of_nm1Cr[i] = 0;  // set to even
        }
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (parity_of_nm1Cr[i]) ans ^= a[i];
    }
    cout << ans << endl;
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
