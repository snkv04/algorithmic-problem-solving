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

void solve() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << "0\n";
        return;
    }

    vector<int> a(n);
    cin >> a;
    for (int i = 0; i < n; ++i) --a[i];

    vector<vector<int>> ops;
    while (true) {
        // gets indices
        vector<int> idx(n);
        for (int i = 0; i < n; ++i) {
            idx[a[i]] = i;
        }

        // finds 2 values to un-invert
        int v1 = -1, v2 = -1;
        for (int i = 0; i < n - 1; ++i) {
            if (idx[i] > idx[i + 1]) {
                v1 = i;
                v2 = i + 1;
                break;
            }
        }
        if (v1 == -1) {
            break;
        }

        // comes up with operation
        int s1 = 0, s2 = idx[v2], s3 = -1, s4 = idx[v1] + 1;
        for (int i = idx[v2]; i < idx[v1]; ++i) {
            if (a[i] > a[i + 1]) {
                s3 = i + 1;
                break;
            }
        }
        
        // places operation on list
        vector<int> op;
        if (s2 > s1) op.push_back(s2 - s1);
        if (s3 > s2) op.push_back(s3 - s2);
        if (s4 > s3) op.push_back(s4 - s3);
        if (n > s4) op.push_back(n - s4);
        ops.push_back(op);

        // performs operation
        vector<int> newa;
        for (int i = s4; i < n; ++i) newa.push_back(a[i]);
        for (int i = s3; i < s4; ++i) newa.push_back(a[i]);
        for (int i = s2; i < s3; ++i) newa.push_back(a[i]);
        for (int i = s1; i < s2; ++i) newa.push_back(a[i]);
        a = std::move(newa);
    }

    cout << ops.size() << "\n";
    for (auto op : ops) {
        cout << op.size() << " ";
        for (int sz : op) cout << sz << " ";
        cout << "\n";
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
