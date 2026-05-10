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
    vector<ll> steps(3);
    cin >> steps;
    ll m;
    cin >> m;

    // gets LCM of each combination/subset of steps
    vector<ll> lcms(8, 1);
    for (int mask = 1; mask < 8; ++mask) {
        for (int i = 0; i < 3; ++i) {
            if ((mask >> i) & 1) {
                lcms[mask] = lcm(lcms[mask], steps[i]);
            }
        }
    }

    // finds the number of times each LCM fits into m, without worrying about double-counting
    vector<ll> raw_num_times(8, 0);
    for (int mask = 1; mask < 8; ++mask) {
        raw_num_times[mask] = m / lcms[mask];
    }

    // gets the number of days each subset appears on its own (without overlapping with another subset);
    // so, basically, this handles double-counting
    vector<ll> modified_num_times = raw_num_times;
    for (int mask = 1; mask < 8; ++mask) {
        for (int superset = mask + 1; superset < 8; ++superset) {
            if ((superset & mask) == mask) {  // just pure inclusion-exclusion
                ll multiplier = 1;
                if (__builtin_popcountll(superset) % 2 != __builtin_popcountll(mask) % 2) {
                    multiplier = -1;
                }
                modified_num_times[mask] += multiplier * raw_num_times[superset];
            }
        }
    }

    // if we know how many times each subset appears on its own, then distributing the values into each
    // step (a, b, c) is easy
    vector<ll> ans(3, 0);
    for (int mask = 1; mask < 8; ++mask) {
        ll adding = modified_num_times[mask] * 6 / __builtin_popcountll(mask);
        for (int i = 0; i < 3; ++i) {
            if ((mask >> i) & 1) {
                ans[i] += adding;
            }
        }
    }
    for (int i = 0; i < 3; ++i) cout << ans[i] << " ";
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
