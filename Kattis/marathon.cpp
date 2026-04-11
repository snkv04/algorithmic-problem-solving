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

    ld ans = max(a[0], (int) 5e6 - a[n - 1]);
    for (int i = 0; i < n - 1; ++i) ans = max(ans, (ld) (a[i + 1] - a[i]) / 2.0);

    int ans2 = 0;
    int curr = 0;
    auto find_next = [&](int curr) {
        if (curr == n - 1) return curr;
        int l = curr + 1, r = n - 1, next = curr;
        while (l <= r) {
            int m = (l + r) / 2;
            if (a[m] <= a[curr] + 2 * ans) {
                next = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return next;
    };
    while (curr < n - 1 && a[curr + 1] <= ans) {
        ++ans2;
        ++curr;
    }
    int next = curr;
    while (5e6 - a[curr] > ans && (next = find_next(curr)) != curr) {
        ans2 += next - curr - 1;
        curr = next;
    }
    ans2 += n - 1 - curr;
    
    cout << fixed << setprecision(1) << ans << ' ' << ans2 << endl;
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
