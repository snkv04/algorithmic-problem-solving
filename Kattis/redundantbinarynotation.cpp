#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 998244353;
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

ll dfs(ll n, ll b, ll t, map<pair<ll, ll>, ll> &cache) {
    if (b == 0) {
        assert(b >= 0 && b <= t);
        return 1;
    }
    auto p = make_pair(n, b);
    if (cache.count(p)) return cache[p];

    // two ways to implement this: either check all the base cases at the top of the function (in callee),
    // or in the loop (in caller); in this case, we want to do caller, because as soon as digit gets too big,
    // we don't want to check any more values of digit, which we can do in the caller but not callee
    ll ways = 0;
    for (ll d = 0; d <= t; ++d) {
        if (n < d * (1LL << b)) {
            // bit will be too big
            break;
        } else {
            ll rest = n - d * (1LL << b);
            if ((rest + t - 1) / t > (1LL << b) - 1) {  // can't directly check inequality bc overflow, so divide other side by t
                // bit will be too small
                continue;
            } else {
                ways = (ways + dfs(rest, b - 1, t, cache)) % MOD;
            }
        }
    }
    cache[p] = ways;
    return ways;
}

void solve() {
    ll n, t;
    cin >> n >> t;
    map<pair<ll, ll>, ll> cache;
    cout << dfs(n, 60, t, cache) << endl;
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
