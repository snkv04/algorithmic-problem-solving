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
    a.insert(a.begin(), 0);
    
    vector<int> cnt0(n + 1, 0);
    for (int i = 1; i <= n; ++i) cnt0[i] = cnt0[i - 1] + (a[i] == 0);
    /*
    - `indices` maps from prefix XOR to the indices where it shows up,
    with the indices separated out into odd and even by means of the
    outer level (the 2 elements of the vector)
    */
    vector<map<int, set<int>>> indices(2);
    vector<int> prefsum(n + 1, 0);
    int pref = 0;
    for (int i = 1; i <= n; ++i) {
        pref ^= a[i];
        indices[i % 2][pref].insert(i);
        prefsum[i] = pref;
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        if (cnt0[r] - cnt0[l - 1] == r - l + 1) {
            cout << "0\n";
            continue;
        }
        if ((prefsum[r] ^ prefsum[l - 1]) != 0) {  // xor has lower precedence than equality/inequality?
            cout << "-1\n";
            continue;
        }
        if ((r - l + 1) % 2) {
            cout << "1\n";
            continue;
        }
        if (a[l] == 0 || a[r] == 0) {
            cout << "1\n";
            continue;
        }

        int want = prefsum[l - 1];
        int want_parity = ((l - 1) + 1) % 2;  // just being explicit
        auto it = indices[want_parity][want].upper_bound(l - 1);
        if (it == indices[want_parity][want].end()) {
            cout << "-1\n";
        } else {
            int index = *it;
            if (index > r) {
                cout << "-1\n";
            } else {
                cout << "2\n";
            }
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
