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
    if (n % 4 == 1 || n % 4 == 2) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    if (n % 4 == 3) {
        vector<int> a, b;
        a.push_back(1); a.push_back(2);
        b.push_back(3);
        for (int i = 4; i <= (n - 3) / 2 + 3; i += 2) {
            a.push_back(i);
            a.push_back(n + 4 - i);
        }
        for (int i = 5; i <= (n - 3) / 2 + 3; i += 2) {
            b.push_back(i);
            b.push_back(n + 4 - i);
        }

        cout << a.size() << "\n";
        for (int num : a) cout << num << " ";
        cout << "\n" << b.size() << "\n";
        for (int num : b) cout << num << " ";
        cout << "\n";
    } else {
        cout << n / 2 << "\n";
        for (int i = 1; i < n / 2; i += 2) {
            cout << i << " " << n + 1 - i << " ";
        }
        cout << "\n" << n / 2 << "\n";
        for (int i = 2; i <= n / 2; i += 2) {
            cout << i << " " << n + 1 - i << " ";
        }
        cout << "\n";
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
