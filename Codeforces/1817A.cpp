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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;

    vector<pair<int, int>> segments;
    int last = -1;
    for (int i = 0; i < n; ++i) {
        if (i == n - 1 || a[i] < a[i + 1]) {
            segments.push_back(make_pair(last + 1, i));
            last = i;
        }
    }

    vector<int> pref_sums(n, 0);
    int pref = 0;
    for (auto [l, r] : segments) {
        pref += min(2, r - l + 1);
        pref_sums[r] = pref;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        --l; --r;

        int lo = 0, hi = segments.size() - 1, l_idx = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (segments[mid].second >= l) {
                l_idx = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        lo = 0; hi = segments.size() - 1; int r_idx = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (segments[mid].first <= r) {
                r_idx = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        if (l_idx == r_idx) {
            cout << min(2, r - l + 1) << '\n';
        } else {
            int left = min(2, segments[l_idx].second - l + 1);
            int right = min(2, r - segments[r_idx].first + 1);
            int middle = pref_sums[segments[r_idx].first - 1] - pref_sums[segments[l_idx].second];
            cout << left + right + middle << endl;
        }
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
