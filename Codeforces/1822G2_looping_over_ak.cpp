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
    /*
    - problem:
        - given an array, find the number of ordered 3-tuples of indices whose corresponding values in the array
        form a geometric sequence
    - solution:
        - iterate over all a_k, and break down the [a_i, a_j, a_k] windows into two groups:
            - those whose a_i is >= cbrt(a_k), so we can loop over b in O(cbrt(a_k))
            - those whose a_i is < cbrt(a_k), so we can loop over a_i in O(cbrt(a_k))
    - details:
        - try to rely on multiplication instead of sqrt or division
        - when the time limit is tight, try to wrap anything expensive (like even a sqrt) inside of if conditions
    */

    int n;
    cin >> n;
    vector<ll> a(n);
    cin >> a;

    // case 1: b = 1
    map<ll, ll> freq; for (ll ai : a) freq[ai] += 1;
    ll ans = 0;
    for (auto [ai, f] : freq) {
        ans += f * (f - 1) * (f - 2);
    }

    // case 2: b > 1
    auto cnt = [&](ll x) { return freq.find(x) == freq.end() ? 0 : freq[x]; };
    for (auto [ak, f] : freq) {
        for (int i = 1; i * i * i <= ak; ++i) {
            // treat i as b, so the loop spreads a_i down to cbrt(a_k)
            int b = i;
            if (
                b > 1 &&
                ak % (b * b) == 0
            ) {
                ans += cnt(ak / (b * b)) * cnt(ak / b) * f;
            }

            // treat i as a_i, so the loop shortens the [a_i, a_j, a_k] window so that
            // a_i goes up to being cbrt(a_k)
            int ai = i;
            if (ak % ai == 0) {
                int b2 = sqrt(ak / ai);
                if (
                    ai * ai * ai != ak &&
                    b2 > 1 &&
                    ai * b2 * b2 == ak
                ) {
                    ans += cnt(ai) * cnt(ai * b2) * f;
                }
            }
        }
    }
    cout << ans << '\n';
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
