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
    vector<vector<int>> a(n);
    for (int i = 0; i < n; ++i) {
        int l;
        cin >> l;
        a[i].resize(l);
        cin >> a[i];
        reverse(a[i].begin(), a[i].end());

        // gets rid of duplicates
        vector<int> newai;
        set<int> seen;
        for (int j = 0; j < l; ++j) {
            if (!seen.count(a[i][j])) {
                newai.push_back(a[i][j]);
                seen.insert(a[i][j]);
            }
        }
        a[i] = std::move(newai);
    }
    
    set<int> used;
    vector<int> q;
    while (a.size()) {
        sort(a.begin(), a.end());
        for (int num : a[0]) {
            if (!used.count(num)) {
                q.push_back(num);
                used.insert(num);
            }
        }
        a.erase(a.begin());

        for (int i = 0; i < a.size(); ++i) {
            vector<int> newai;
            for (int j = 0; j < a[i].size(); ++j) {
                if (!used.count(a[i][j])) newai.push_back(a[i][j]);
            }
            a[i] = std::move(newai);
        }
    }

    for (int i = 0; i < q.size(); ++i) {
        cout << q[i] << " ";
    }
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
