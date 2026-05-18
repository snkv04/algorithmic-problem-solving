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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    cin >> a >> b;

    ll ans = 0, summem = 0;
    vector<ll> mem(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        if (a[i] == 1 && b[i] == 1) {
            mem[1] += mem[0];
            mem[0] = 0;
            mem[1] += 1; summem += 1;
        } else if (a[i] == 1 || b[i] == 1) {
            int x = (a[i] == 1) ? b[i] : a[i];
            summem -= mem[0]; mem[0] = 0;
            summem -= mem[x - 1]; mem[x - 1] = 0;
        } else if (a[i] == b[i]) {
            int x = a[i];
            mem[0] += 1; summem += 1;
            mem[x] += mem[x - 1];
            mem[x - 1] = 0;
        } else {
            int x = a[i], y = b[i];
            summem -= mem[x - 1]; mem[x - 1] = 0;
            summem -= mem[y - 1]; mem[y - 1] = 0;
            mem[0] += 1; summem += 1;
        }
        ans += summem;
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
