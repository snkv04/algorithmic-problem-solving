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
std::ostream& operator<<(std::ostream &os, const std::deque<T> &c) {
    os << "[";
    for (int i = 0; i < c.size(); ++i) cout << c[i] << ", ";
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
    - i was confused during the contest because i was trying to figure out the best strategy when there are multiple
    pivots. but we basically just have to reframe "flipping consecutive segments", where a segment consists of all
    0s or all 1s, into "pulling in 2 boundaries" (or "erasing 2 boundaries"). once we do that, then it's clear that
    we want to pair segments that have some pivot in between them, which maps onto the classical problem of pairing
    items from different sets; in this case, the sets are the boundaries between consecutive pivots, so pivots separate
    sets. we want to maximize the number of pairs in order to minimize the number of operations; if we can't pair all
    elements, then we handle the remaining ones individually.
    - how do we know that by doing this pairing strategy, we'll always ensure that each pivot is flipped (meaning that
    we chose an (l, r) containing that pivot) an even number of times? observe that the total number of boundaries
    is always even. furthermore, the number of boundaries in each section is also always even. so we can look at the
    2 steps of our solution: first, when we pair boundaries on opposite sides of each pivot, the number of pairings
    that we'll do is even, and second, when we handle individual unpaired boundaries, we'll always have an even number
    of remaining unpaired boundaries. if we didn't know that the pivots would always land on the same color that they
    started with by doing this pairing, then the original problem wouldn't be equivalent to this pairing problem because
    the original problem requires for that constraint to be met.
    - when moving from the easy problem to the hard problem, we're basically generalizing "taking max of 2 elements"
    to "taking max of (max of all elements) and (half the sum of all elements)", because even in the easy problem,
    we're basically still doing the pairing problem.
    */

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    cin >> a;
    set<int> p;
    for (int i = 0; i < k; ++i) {
        int pi;
        cin >> pi;
        p.insert(pi);
    }
    if (a[*p.begin() - 1] == 0) {
        for (int i = 0; i < n; ++i) a[i] ^= 1;
    }
    a.insert(a.begin(), 1);
    a.push_back(1);

    // boundary counts by segment, where segments have the "special indices" (or "pivots") as their endpoints
    vector<int> counts;
    int count = 0;
    for (int i = 0; i <= n; ++i) {
        count += a[i] != a[i + 1];
        if (i == n || p.count(i + 1)) {
            counts.push_back(count);
            count = 0;
        }
    }

    int sum = 0, mx = 0;
    for (int i = 0; i < counts.size(); ++i) {
        sum += counts[i];
        mx = max(mx, counts[i]);
    }

    if (mx > sum - mx) {
        cout << mx << endl;
    } else {
        cout << sum / 2 << endl;
    }
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
