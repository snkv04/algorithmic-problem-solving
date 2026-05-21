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

// suppose that the segments sums are bounded;
// is it possible for the sum of picked elements to also be within this bound?
bool check(vector<int> &a, ll bound) {
    // - mem[i] = minimum sum of picked elements where all segments that we look at have their
    // sum bounded by B
    // - optimizes the 2D DP because we don't care about what the max segment sum is anymore,
    // as long as it's <= B
    int n = a.size() - 1;
    vector<ll> mem(n + 1, 1e15);
    multiset<ll> mem_vals;
    mem[0] = 0;
    mem_vals.insert(0);

    // - use a sliding window to ensure that the segments we consider which end at (i - 1)
    // don't extend too far
    // - works because all array values are nonnegative, so if a segment ends at (r - 1),
    // then pulling l to the right will only (weakly) decrease the segment sum
    // - keeps track of available DP states to draw from in a multiset
    int l = 0;
    ll sum = 0;
    for (int r = 1; r <= n; ++r) {
        assert(mem_vals.size());
        sum += a[r - 1];
        while (sum > bound) {
            mem_vals.erase(mem_vals.find(mem[l]));
            ++l;
            sum -= a[l];
        }

        mem[r] = a[r] + *mem_vals.begin();
        mem_vals.insert(mem[r]);
    }

    // - checks all mem values where the last segment is also bounded by B
    ll best = mem[n];
    sum = 0;
    for (int i = n; i >= 1 && sum + a[i] <= bound; --i) {
        sum += a[i];
        best = min(best, mem[i - 1]);
    }
    return best <= bound;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    a.insert(a.begin(), 0);

    ll mx = 0;
    for (int i = 1; i <= n; ++i) mx = max(mx, (ll) a[i]);

    ll l = mx, r = 1e15, ans = -1;
    while (l <= r) {
        ll m = (l + r) / 2;
        if (check(a, m)) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
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
