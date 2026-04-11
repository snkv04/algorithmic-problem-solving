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

vector<vector<ll>> eye(int n) {
    vector<vector<ll>> i(n, vector<ll>(n, 0));
    for (int k = 0; k < n; ++k) i[k][k] = 1;
    return i;
}

vector<vector<ll>> mat_mul(const vector<vector<ll>> a, const vector<vector<ll>> b) {
    assert(a[0].size() == b.size());
    vector<vector<ll>> c(a.size(), vector<ll>(b[0].size(), 0));
    for (int i = 0; i < a.size(); ++i) {
        for (int j = 0; j < b[0].size(); ++j) {
            for (int k = 0; k < a[0].size(); ++k) {
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return c;
}

vector<vector<ll>> mat_exp(const vector<vector<ll>> m, ll e) {
    if (e == 0) return eye(m.size());
    if (e % 2) return mat_mul(m, mat_exp(m, e - 1));
    else return mat_exp(mat_mul(m, m), e / 2);
}

void solve() {
    /*
    how do we define this in terms of matrix exponentiation?

    we have f(n), f(n-1), f(n-2).

    and we want f(n'), f(n'-1), f(n'-2), where
    n' = n+1
    f(n') = f(n+1) = 1 + f(n) + f(n-1)
    f(n'-1) = f(n)
    f(n'-2) = f(n-1)

    so we can use a length-4 vector, where v[0]=f(n), v[1]=f(n-1), v[2]=f(n-2), and v[3]=1.
    then the transition matrix is literally just defined by the above equations.
    */

    vector<vector<ll>> transition = {
        {1, 1, 0, 1},
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 1},
    };
    vector<vector<ll>> v = {
        {0},
        {0},
        {0},
        {1},
    };

    ll n;
    cin >> n;
    auto full_transition = mat_exp(transition, n);
    auto final_v = mat_mul(full_transition, v);
    cout << final_v[0][0] << endl;
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
