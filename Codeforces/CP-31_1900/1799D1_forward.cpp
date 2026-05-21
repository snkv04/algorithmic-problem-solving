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
    int n, k;
    cin >> n >> k;
    vector<int> a(n), cold(k), hot(k);
    cin >> a >> cold >> hot;
    a.insert(a.begin(), 0);
    cold.insert(cold.begin(), 0);
    hot.insert(hot.begin(), 0);

    /*
    - write it so simply that i can easily memorize it
    - mem[i][j] = minimum cost on prefix ending at index i, where we assume program i is on the black CPU
    and j is the color of the last program on the white CPU
    - for a given index, if we look at the color of the last program on the same CPU, we can figure out if
    we're going to be hot or cold
    */
    vector<vector<ll>> mem(n + 1, vector<ll>(k + 1, 1e15));
    mem[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        /*
        - we put i and (i - 1) on the same CPU, so:
            - the "last program on white CPU" information propagates
            - the heat of the program depends on the connection between i and (i - 1)        
        - algorithm: iterate over all "last program on white" from index (i - 1)
        */
        for (int j = 0; j <= k; ++j) {
            mem[i][j] = mem[i - 1][j] + (a[i] == a[i - 1] ? hot[a[i]] : cold[a[i]]);
        }

        /*
        - we put i and (i - 1) on different CPUs, so:
            - we assumed (i - 1) was on black, but now we're assuming that i is on black, so we "flip"
            the previous state, meaning that:
                - the new "last program on white CPU" is (i - 1)
                - the previous "last program on white" is now the last program on black,
                so heat of program depends on connection between i and previous last on white
        - algorithm: again, iterate over all "last program on white" from index (i - 1)
        */
        for (int j = 0; j <= k; ++j) {
            mem[i][a[i - 1]] = min(
                mem[i][a[i - 1]],
                mem[i - 1][j] + (a[i] == j ? hot[a[i]] : cold[a[i]])
            );
        }
    }

    ll ans = 1e15;
    for (int j = 0; j <= k; ++j) ans = min(ans, mem[n][j]);
    cout << ans << endl;
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
