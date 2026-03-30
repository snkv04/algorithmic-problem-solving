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

void solve_On_space() {
    /*
    - moral of the story: if allocating a large multidimensional vector (i.e., on the order of 1e7),
    then better to make the inner dynamic vectors into static arrays, because heap allocations bad :((
        - in general, if allocating a large array, try to optimize things, as 1e7 elements starts to
        get near the limit
    */

    int n;
    cin >> n;
    vector<array<ll, 2>> mem(n+1, array<ll, 2>({0}));
    mem[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        mem[i][0] = (3 * mem[i-1][1]) % MOD;
        mem[i][1] = (mem[i-1][0] + 2 * mem[i-1][1]) % MOD;
    }
    cout << mem[n][0] << endl;
}

void solve_O1_space() {
    int n;
    cin >> n;
    vector<ll> mem = {1, 0};
    for (int i = 1; i <= n; ++i) {
        vector<ll> new_mem(2, 0);
        new_mem[0] = (3 * mem[1]) % MOD;
        new_mem[1] = (mem[0] + 2 * mem[1]) % MOD;
        mem = std::move(new_mem);
    }
    cout << mem[0] << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        // solve_On_space();
        solve_O1_space();
    }

    return 0;
}
