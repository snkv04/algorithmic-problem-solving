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

    map<int, int> l, r, freq;
    for (int i = 0; i < n; ++i) {
        if (!l.count(a[i])) {
            l[a[i]] = i;
        }
        r[a[i]] = i;
        freq[a[i]] += 1;
    }

    int mex = 0;
    while (l.count(mex)) ++mex;

    if (l.count(mex + 1)) {
        bool valid = true;
        for (int i = 0; i < mex; ++i) {
            if (l[mex + 1] < l[i] && r[i] < r[mex + 1]) {
                valid = false;
                break;
            }
        }
        cout << (valid ? "yes" : "no") << endl;
    } else {
        if (l.upper_bound(mex + 1) != l.end()) {
            cout << "yes" << endl;
        } else {
            bool found = false;
            for (int i = 0; i < mex; ++i) {
                if (freq[i] > 1) {
                    found = true;
                    break;
                }
            }
            cout << (found ? "yes" : "no") << endl;
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
