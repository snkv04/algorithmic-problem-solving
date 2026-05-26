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

ll mod_pow(ll b, ll e) {
    if (e == 0) return 1;
    if (e % 2) return mod_pow(b, e - 1) * b % MOD;
    else return mod_pow(b * b % MOD, e / 2) % MOD;
}

ll mod_inv(ll x) {
    return mod_pow(x, MOD - 2);
}

ll mod_div(ll n, ll d) {
    return n * mod_inv(d) % MOD;
}

void process_candidate(ll p, ll q, ll x, ll y, ll &ans, ll &ansp, ll &ansq) {
    if ((p & q) == 0 && abs(x - p) + abs(y - q) < ans) {
        ansp = p;
        ansq = q;
        ans = abs(x - p) + abs(y - q);
    }
}

void solve() {
    /*
    key ideas:
    - we have some bits we want to "fix". they are the bits where x and y overlap. instead of fixing all, we can look
    at the most significant one that we want to fix, and fix all to the right of it. this might make something to the
    left break, but we check our conditions on every candidate, and one of the 4 candidates won't break anything to the left.
    - suppose a bit b is activated (equal to 1) on both x and y. then we can either set x to 0 and leave y as 1, or the
    reverse. the two cases are the exact same. let's look at x -> 0 and y -> 1. then, we can either:
        - move x up to closest value where bit b is 0. to do this, increase x to the next multiple of 2^b;
        since b'th bit is 1 beforehand, this makes the b'th bit now 0.
        then, everything to the right is fixed automatically, and y can stay the same.
        - move x down to closest value where bit b is 0. to do this, decrease x to 1 below the previous multiple of 2^b.
        then, everything to the right is a 1 on x, so we make everything to the right a 0 on y.
    */
    
    ll x, y;
    cin >> x >> y;

    ll ans = 1e18, ansp = -1, ansq = -1;
    process_candidate(x, y, x, y, ans, ansp, ansq);  // in case x and y already don't overlap on any bits
    for (ll i = 30; i >= 0; --i) {
        if (((x & y) >> i) & 1) {
            process_candidate(
                (x >> i << i) + (1LL << i), y,
                x, y, ans, ansp, ansq
            );
            process_candidate(
                (x >> i << i) - 1, y >> i << i,
                x, y, ans, ansp, ansq
            );
            process_candidate(
                x, (y >> i << i) + (1LL << i),
                x, y, ans, ansp, ansq
            );
            process_candidate(
                x >> i << i, (y >> i << i) - 1,
                x, y, ans, ansp, ansq
            );
            break;
        }
    }
    cout << ansp << " " << ansq << "\n";
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
