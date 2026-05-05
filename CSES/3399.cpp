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
    int n, a, b;
    cin >> n >> a >> b;
    if (a + b > n) {
        cout << "NO\n";
        return;
    }
    if (a + b == 0) {
        cout << "YES\n";
        for (int t = 0; t < 2; ++t) {
            for (int i = 1; i <= n; ++i) {
                cout << i << " ";
            }
            cout << "\n";
        }
        return;
    }
    if (min(a, b) == 0) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    vector<int> first, second;
    int draws = n - a - b;
    for (int i = n; i > n - draws; --i) {
        first.push_back(i);
        second.push_back(i);
    }
    n -= draws;

    for (int i = 1; i <= a; ++i) {
        first.push_back(n - a + i);
        second.push_back(i);
    }
    for (int i = 1; i <= b; ++i) {
        second.push_back(n - b + i);
        first.push_back(i);
    }

    for (int card : first) cout << card << " ";
    cout << "\n";
    for (int card : second) cout << card << " ";
    cout << "\n";
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
