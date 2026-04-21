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

void solve() {
    /*
    - solution:
        - we can basically separate the subsets out into those where a[0] is the max element, a[1] is the max element, etc.
        - then, for each, we can use knapsack to find the number of subsets with each sum, and for a given subset sum
        where a[i] is the max element, it's straightforward to find the value of such a subset
        - basically, knapsack helps here because for a given subset, if we know the sum and the max element, we don't
        need more information about it, so we can just keep track of the number of subsets with a given sum without recording
        what those subsets are
    - useful ideas:
        - see if you can partition your search space into something intuitive; here, we have 2^n subsets, but they
        can be blocked into those with a[0] being the max element, a[1] being the max element, etc.
        - when doing ceiling division and multiplying it with something else, make sure the ceiling division is
        enclosed in parentheses, so then the other factor doesn't mess with the truncation logic
            - more generally, just always use parentheses in order to be extra-explicit with the code
    */

    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    ll ans = 0;
    vector<ll> num_ways(5001, 0);  // num_ways[i] = number of subsets whose sum is equal to i
    num_ways[0] = 1;
    sort(a.begin(), a.end());
    for (int i = 0; i < n; ++i) {
        for (int j = 5000; j >= a[i]; --j) {
            if (j > a[i] * 2) {
                ans = (ans + num_ways[j - a[i]] * ((j + 1) / 2) % MOD) % MOD;
            } else {
                ans = (ans + num_ways[j - a[i]] * a[i]) % MOD;
            }
            num_ways[j] = (num_ways[j] + num_ways[j - a[i]]) % MOD;
        }
    }
    cout << ans << endl;
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
