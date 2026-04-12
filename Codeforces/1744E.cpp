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

map<ll, ll> prime_factorization(ll x) {
    ll rt = sqrt(x);
    map<ll, ll> res;
    for (ll d = 2; d <= rt; ++d) {
        while (x % d == 0) {
            res[d] += 1;
            x /= d;
        }
    }
    if (x > 1) res[x] += 1;
    return res;
}

ll exp(ll b, ll e) {
    if (e == 0) return 1;
    if (e % 2) return b * exp(b, e - 1);
    else return exp(b * b, e / 2);
}

bool recurse(
    map<ll, ll>::iterator &it,
    ll divisor,
    pair<ll, ll> &ans,
    const map<ll, ll> &pf,
    ll a, ll b, ll c, ll d
) {
    if (it == pf.end()) {
        ll other = a * b / divisor;
        ll x = c / divisor * divisor, y = d / other * other;
        if (x > a && y > b) {
            ans = {x, y};
            return true;
        } else {
            return false;
        }
    }

    for (int e = 0; e <= it->second; ++e) {
        ll mult = exp(it->first, e);
        ++it;
        if (recurse(it, divisor * mult, ans, pf, a, b, c, d)) {
            return true;
        } else {
            --it;
        }
    }
    return false;
}

void solve() {
    // solve trivial case
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    if (a == 1 && b == 1) {
        cout << c << " " << d << "\n";
        return;
    }
    
    // get prime factorization of a*b through prime factorization of a and b
    map<ll, ll> apf = prime_factorization(a), bpf = prime_factorization(b);
    map<ll, ll> pf;
    for (auto [k, v] : apf) {
        if (bpf.count(k)) {
            pf[k] = v + bpf[k];
            bpf.erase(k);
        } else {
            pf[k] = v;
        }
    }
    for (auto [k, v] : bpf) {
        assert(!pf.count(k));
        pf[k] = v;
    }
    
    // iterate through all divisors k of a*b. for each, find k' = a*b/k, and see if there's some multiple of
    // k in (a, c] (which will be x) and some multiple of k' in (b, d] (which will be y).
    // core idea: instead of iterating over each x, we iterate over factors of a*b, knowing that x must be
    // divisible by that factor and y must be divisible by the "other" factor of a*b. basically, x and y can
    // be scaled up or down arbitrarily, as long as those 2 conditions hold.
    // the main difference between the easy and hard version is just the thing that we iterate over; we can
    // iterate over fewer things while still finding what we want.
    auto it = pf.begin();
    ll divisor = 1;
    pair<ll, ll> ans = {-1, -1};
    recurse(it, divisor, ans, pf, a, b, c, d);
    cout << ans.first << " " << ans.second << "\n";
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
