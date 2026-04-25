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

int bit_to_sign(int bit) {
    return 2 * bit - 1;
}

void solve() {
    /*
    - core idea:
        - additions are simple expressions. if we want to maximize them, maximize the components separately.
        in specific, instead of picking the best (i, j) pair, we can optimize i and j separately.
        - absolute values are more complex.
            - if we want to maximize an absolute value that adds both i and j (subtractions count),
            we can recognize that the absolute value of something is just the max of 2 cases: when the operand is
            negative and when the operand is positive. we can look at each case separately, and for each, we can
            reduce it to a standard addition. in other words, we optimize i and j separately, after breaking the
            absolute value into simple cases.
            - if we want to maximize an addition of absolute values, recognize that we're maximizing the addition
            of two max() functions; we can look through all combinations of cases for the first function, cases
            for the second function, etc.
    */

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    cin >> a >> b;

    ll sum = 0;
    for (int i = 0; i < n; ++i) sum += abs(b[i] - a[i]);

    ll best_delta = -1e18;
    for (int mask = 0; mask < 4; ++mask) {
        ll best_mask_delta = -1e18, best_j = -1e18;
        for (int i = 0; i < n; ++i) {
            best_mask_delta = max(
                best_mask_delta,
                (ll) -abs(a[i] - b[i]) + bit_to_sign(mask & 1) * a[i] + bit_to_sign(mask >> 1) * b[i] + best_j
            );

            best_j = max(
                best_j,
                (ll) bit_to_sign((mask ^ 3) & 1) * b[i] + bit_to_sign((mask ^ 3) >> 1) * a[i] - abs(a[i] - b[i])
            );
        }
        best_delta = max(best_delta, best_mask_delta);
    }
    sum = max(sum, sum + best_delta);
    cout << sum << endl;
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
