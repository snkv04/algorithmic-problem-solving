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

void solve(string s) {
    if (s == "first") {
        int n;
        cin >> n;
        vector<int> p(n);
        cin >> p;

        for (int i = 0; i < n; ++i) {
            if (p[i] == 1) {
                cout << 1 << endl;
                return;
            } else if (p[i] == n) {
                cout << 0 << endl;
                return;
            }
        }
    } else {
        int n, x;
        cin >> n >> x;
        int lo = 1, hi = n, r = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            cout << "? 1 " << mid << endl;
            int res;
            cin >> res;
            if (res == n - 1) {
                r = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        lo = 1; hi = r; int l = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            cout << "? " << mid << " " << r << endl;
            int res;
            cin >> res;
            if (res == n - 1) {
                l = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        if (x) {
            cout << "! " << r << endl;
        } else {
            cout << "! " << l << endl;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int t = 1;
    cin >> t;
    while (t--) {
        solve(s);
    }

    return 0;
}
