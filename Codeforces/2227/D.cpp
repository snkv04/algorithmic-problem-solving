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
    n *= 2;
    vector<int> a(n);
    cin >> a;

    int idx1 = -1, idx2 = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] == 0) {
            if (idx1 == -1) idx1 = i;
            else idx2 = i;
        }
    }

    vector<pair<int, int>> candidates;
    auto propagate = [&](int l, int r) {
        while (l - 1 >= 0 && r + 1 < n && a[l - 1] == a[r + 1]) {
            --l;
            ++r;
        }
        return make_pair(l, r);
    };
    candidates.push_back(propagate(idx1, idx1));
    candidates.push_back(propagate(idx2, idx2));
    int m = (idx1 + idx2) / 2;
    if (idx1 % 2 == idx2 % 2) {
        candidates.push_back(propagate(m, m));
    } else {
        int m2 = m + 1;
        if (a[m] == a[m2]) {
            candidates.push_back((propagate(m, m2)));
        }
    }

    int ans = 0;
    auto get_mex = [&](pair<int, int> &p) {
        auto [l, r] = p;
        set<int> have;
        for (int i = l; i <= r; ++i) have.insert(a[i]);
        int mex = 0;
        while (have.count(mex)) ++mex;
        return mex;
    };
    for (auto p : candidates) ans = max(ans, get_mex(p));
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
