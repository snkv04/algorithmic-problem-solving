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

// struct Comparator {
//     bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
//         if (a.first != b.first) {
//             return a.first < b.first;
//         } else {
//             return a.second < b.second;
//         }
//     }
// };

void solve() {
    int n, m;
    cin >> n >> m;

    multiset<int> a;
    while (n--) {
        int ai;
        cin >> ai;
        a.insert(ai);
    }
    vector<int> b(m), c(m); cin >> b >> c;
    vector<pair<int, int>> good, bad;
    for (int i = 0; i < m; ++i) {
        if (c[i]) {
            good.push_back({b[i], c[i]});
        } else {
            bad.push_back({b[i], c[i]});
        }
    }
    sort(good.begin(), good.end());
    sort(bad.begin(), bad.end());

    int ans = 0;
    for (auto [health, newval] : good) {
        auto it = a.lower_bound(health);
        if (it != a.end()) {
            int damage = *it;
            a.erase(a.find(damage));
            damage = max(damage, newval);
            a.insert(damage);
            ++ans;
        }
    }
    for (auto [health, newval] : bad) {
        auto it = a.lower_bound(health);
        if (it != a.end()) {
            int damage = *it;
            a.erase(a.find(damage));
            ++ans;
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
