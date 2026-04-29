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

    // - mem[i][j] = minimum possible sum of picked elements that we can reach where we've looked at
    // indices [0, ..., i], we are picking/blocking index i, and the maximum segment sum is j
    // - optimizes the 3D DP by keeping track of the minimum k value that's reachable instead of keeping
    // track of all reachable k values
    vector<map<ll, ll>> mem(n + 1);
    mem[0][0] = 0;

    // we have index i picked
    for (int i = 1; i <= n; ++i) {
        ll seg_sum = 0;

        // iterates over last picked element, so the segment is the open interval (j + 1, i - 1)
        for (int j = i - 1; j >= 0; --j) {
            // iterates over states at j, and updates (or inserts) reachable states for index i
            for (auto [k, v] : mem[j]) {
                ll new_max_seg_sum = max(k, seg_sum);
                ll new_picked_sum = v + a[i];
                if (mem[i].count(new_max_seg_sum)) {
                    mem[i][new_max_seg_sum] = min(mem[i][new_max_seg_sum], new_picked_sum);
                } else {
                    mem[i][new_max_seg_sum] = new_picked_sum;
                }
            }
            seg_sum += a[j];
        }
    }

    ll ans = 1e15;
    vector<ll> pref(n + 1, 0); for (int i = 1; i <= n; ++i) pref[i] = pref[i - 1] + a[i];
    for (int i = 1; i <= n; ++i) {
        for (auto [max_seg_sum, min_picked_sum] : mem[i]) {
            // for a state, the corresponding value is max of "max of segment sums to left",
            // min sum of picked elements, sum of elements to right
            ans = min(ans, max({max_seg_sum, min_picked_sum, pref[n] - pref[i]}));
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
