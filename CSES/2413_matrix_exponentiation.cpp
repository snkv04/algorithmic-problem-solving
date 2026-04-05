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

vector<vector<ll>> matmul(vector<vector<ll>> a, vector<vector<ll>> b) {
    assert(a[0].size() == b.size());
    int r = a.size(), c = b[0].size();
    vector<vector<ll>> result(r, vector<ll>(c, 0));
    for (int k = 0; k < a[0].size(); ++k) {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return result;
}

vector<vector<ll>> identity(int n) {
    vector<vector<ll>> i(n, vector<ll>(n, 0));
    for (int r = 0; r < n; ++r) i[r][r] = 1;
    return i;
}

vector<vector<ll>> matexp(vector<vector<ll>> m, ll e) {
    assert(m.size() == m[0].size());

    if (e == 0) return identity(m.size());

    if (e % 2) return matmul(m, matexp(m, e - 1));
    else return matexp(matmul(m, m), e / 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<ll>> transition = {
        {4, 1},
        {1, 2}
    };
    vector<vector<ll>> start = {
        {1},
        {1}
    };

    int t = 1;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        auto end = matmul(matexp(transition, n - 1), start);
        ll ans = (end[0][0] + end[1][0]) % MOD;
        cout << ans << endl;
    }

    return 0;
}
