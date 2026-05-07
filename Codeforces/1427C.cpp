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
    /*
    - key idea:
        - if we let t_j go back far enough, then it is guaranteed that we can reach (x_i, y_i) from (x_j, y_j)
        in time
    - general idea:
        - instead of brute-force checking all choices, check to see if some choices are guaranteed to be always
        true/reachable or false/unreachable so we only have to check the others
    */

    int r, n;
    cin >> r >> n;
    vector<array<int, 3>> points;
    points.push_back({0, 1, 1});
    for (int i = 1; i <= n; ++i) {
        int t, x, y;
        cin >> t >> x >> y;
        points.push_back({t, x, y});
    }

    // mem[i] = maximum number of celebs we can get if we look at celebs {1, ..., i} AND we include i;
    // it is -INF if we cannot reach celeb #i through any means, so we should initialize to -INF to avoid
    // making assumptions...
    int ans = 0;
    constexpr int INF = 1e9;
    vector<int> mem(n + 1, -INF);
    mem[0] = 0;
    int window_left = 0, best_before_window = -INF;
    for (int i = 1; i <= n; ++i) {
        while (points[window_left][0] <= points[i][0] - 2 * (r - 1) && window_left < i) {
            best_before_window = max(best_before_window, mem[window_left]);
            ++window_left;
        }

        int best_in_window = -INF;  // this is important! we don't want to preemptively assume we can come to i from somewhere
        for (int j = i - 1; j >= window_left; --j) {
            if (
                mem[j] != -INF &&  // probably unnecessary
                points[i][0] - points[j][0] >= abs(points[i][1] - points[j][1]) + abs(points[i][2] - points[j][2])
            ) {
                best_in_window = max(best_in_window, mem[j]);
            }
        }

        int best = max(best_before_window, best_in_window);
        if (best != -INF) {
            mem[i] = 1 + best;
        }
        ans = max(ans, mem[i]);
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
