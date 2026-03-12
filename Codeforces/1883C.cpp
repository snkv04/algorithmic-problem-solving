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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    cin >> a;

    map<int, int> f;
    for (int ai : a) f[ai] += 1;

    vector<int> primes = {2, 3, 5};
    if (std::find(primes.begin(), primes.end(), k) != primes.end()) {
        for (int i = k; i <= 10; i += k) {
            if (f.find(i) != f.end()) {
                cout << "0\n";
                return;
            }
        }

        int mx = 0;
        for (auto [key, v] : f) {
            mx = max(mx, key % k);
        }
        cout << k - mx << '\n';
    } else {
        assert(k == 4);
        if (f.find(4) != f.end() || f.find(8) != f.end()) {
            cout << "0\n";
            return;
        }

        int others = 0;
        for (int i = 2; i <= 10; i += 4) {
            if (f.find(i) != f.end()) others += f[i];
        }
        if (others >= 2) {
            cout << "0\n";
            return;
        }

        if (others == 0) {
            if (n == 1) {
                cout << 4 - (a[0] % 4) << '\n';
            } else {
                bool found3 = false;
                for (int ai : a) if (ai % 4 == 3) { found3 = true; break; }
                if (found3) {
                    cout << "1\n";
                } else {
                    cout << "2\n";
                }
            }
        } else {
            assert(others == 1);
            if (n == 1) {
                cout << "2\n";
            } else {
                cout << "1\n";
            }
        }
    }
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
