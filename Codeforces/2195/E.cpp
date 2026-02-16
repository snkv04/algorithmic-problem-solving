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

void dfs(int node, vector<int> &l, vector<int> &r, vector<int> &time) {
    if (l[node] == -1) return;

    dfs(l[node], l, r, time);
    dfs(r[node], l, r, time);
    time[node] = (time[l[node]] + time[r[node]] + 4) % MOD;
}

void dfs2(int node, int prevtime, vector<int> &time, vector<int> &time2, vector<int> &l, vector<int> &r) {
    time2[node] = (prevtime + time[node] + 1) % MOD;

    if (l[node] != -1) {
        dfs2(l[node], time2[node], time, time2, l, r);
        dfs2(r[node], time2[node], time, time2, l, r);
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        --l[i]; --r[i];
    }

    vector<int> time(n, 0);
    dfs(0, l, r, time);
    vector<int> time2(n, 0);
    dfs2(0, 0, time, time2, l, r);

    for (int i = 0; i < n; ++i) cout << time2[i] << " ";
    cout << "\n";
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
