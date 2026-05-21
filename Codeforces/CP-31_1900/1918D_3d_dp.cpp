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
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    a.insert(a.begin(), 0);

    // - mem[i][j][k] = whether or not it's possible to reach a state where we've looked at indices [0, ..., i],
    // we are picking/blocking index i, the maximum segment sum is j, and the sum of picked elements is k
    // - optimizes the 4D DP by only assuming that i is at the end of a segment, so we don't track the curr seg sum,
    // since the length (and sum) of a segment is already known based on what state we're drawing from
    vector<set<pair<ll, ll>>> mem(n + 1);
    mem[0].insert({0, 0});

    // we have index i picked
    for (int i = 1; i <= n; ++i) {
        ll seg_sum = 0;

        // iterates over last picked element, so the segment is the open interval (j + 1, i - 1)
        for (int j = i - 1; j >= 0; --j) {
            // iterates over states at j, and inserts new reachable states for index i
            for (auto [max_seg_sum, picked_sum] : mem[j]) {
                ll new_max_seg_sum = max(max_seg_sum, seg_sum);
                ll new_picked_sum = picked_sum + a[i];
                mem[i].insert(make_pair(new_max_seg_sum, new_picked_sum));
            }
            seg_sum += a[j];
        }
    }

    // iterates over all states, and gets the best state
    ll ans = 1e15;
    vector<ll> pref(n + 1, 0); for (int i = 1; i <= n; ++i) pref[i] = pref[i - 1] + a[i];
    for (int i = 1; i <= n; ++i) {
        for (auto [max_seg_sum, picked_sum] : mem[i]) {
            // for a state, the corresponding value is max of "max of segment sums to left",
            // sum of picked elements, sum of elements to right
            ans = min(ans, max({max_seg_sum, picked_sum, pref[n] - pref[i]}));
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
