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
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    a.insert(a.begin(), 0);

    vector<ll> pref(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i - 1] + a[i];
    }

    map<int, int> segments;
    multiset<ll> sums;
    segments[n] = 1;
    sums.insert(pref[n]);
    for (int i = 1; i <= n; ++i) {
        int idx;
        cin >> idx;

        auto it = segments.lower_bound(idx);
        int l = it->second, r = it->first;
        ll sum = pref[r] - pref[l - 1];
        sums.erase(sums.find(sum));
        segments.erase(it);

        if (l != r) {
            if (idx == l) {
                segments[r] = l + 1;
                sums.insert(pref[r] - pref[l]);
            } else if (idx == r) {
                segments[r - 1] = l;
                sums.insert(pref[r - 1] - pref[l - 1]);
            } else {
                segments[r] = idx + 1;
                sums.insert(pref[r] - pref[idx]);
                segments[idx - 1] = l;
                sums.insert(pref[idx - 1] - pref[l - 1]);
            }
        }

        cout << (sums.size() ? *sums.rbegin() : 0) << '\n';
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
