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
    string s;
    cin >> s;

    vector<int> cnt(26, 0);
    for (auto c : s) cnt[c - 'A'] += 1;

    int odd_idx = -1;
    for (int i = 0; i < 26; ++i) {
        if (cnt[i] % 2) {
            if (odd_idx == -1) {
                odd_idx = i;
            } else {
                cout << "NO SOLUTION\n";
                return;
            }
        }
    }

    queue<pair<char, int>> que;
    stack<pair<char, int>> stk;
    for (int i = 0; i < 26; ++i) {
        if (cnt[i] && cnt[i] % 2 == 0) {
            auto p = make_pair((char) ('A' + i), cnt[i] / 2);
            que.push(p);
            stk.push(p);
        }
    }

    stringstream ss;
    while (que.size()) {
        auto [c, n] = que.front();
        que.pop();
        while (n--) {
            ss << c;
        }
    }
    if (odd_idx != -1) {
        char c = 'A' + odd_idx;
        while (cnt[odd_idx]--) {
            ss << c;
        }
    }
    while (stk.size()) {
        auto [c, n] = stk.top();
        stk.pop();
        while (n--) {
            ss << c;
        }
    }
    cout << ss.str() << "\n";
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
