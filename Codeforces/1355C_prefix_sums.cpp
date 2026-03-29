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
    - solution:
        - for each z, we want to find the number of pairs (x, y) such that x + y > z
        - so, we first find for each number s the number of pairs (x, y) such that x + y = s
        - then, we iterate through z, and sum up num_pairs[s] across all s > z
    - details:
        - how to do the first part? we iterate over x, and increment num_pairs[s] for all s \in [x+B, x+C].
        this can be done using segment tree (slow) or prefix sums (fast).
        - how to do the second part? we just want to find the sum over an interval of an array. so,
        either use segment tree (slow) ore prefix sums (fast).
    */
    
    // gets input
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    // finds number of valid (x, y) pairs for each s such that s = x + y
    int max_sum = b + c;
    vector<ll> num_ways(max_sum + 2, 0);  // +1 to make max_sum a valid index, and +2 to make decrementing num_ways[max_sum+1] valid
    for (int x = a; x <= b; ++x) {
        num_ways[x + b] += 1;
        num_ways[x + c + 1] -= 1;
    }
    for (int i = 1; i <= max_sum + 1; ++i) num_ways[i] += num_ways[i-1];

    // takes prefix sums, so we can easily find num_ways across an interval of s values
    vector<ll> num_ways_pref = num_ways;
    for (int i = 1; i <= max_sum + 1; ++i) num_ways_pref[i] += num_ways_pref[i-1];

    // for each z, finds number of ways (meaning, number of pairs (x, y)) to make a sum that's > z
    ll ans = 0;
    for (int z = c; z <= min(max_sum - 1, d); ++z)
        ans += num_ways_pref[max_sum] - num_ways_pref[z];
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
