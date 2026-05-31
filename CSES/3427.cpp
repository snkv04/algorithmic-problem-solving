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

ll mod_pow(ll b, ll e) {
    if (e == 0) return 1;
    if (e % 2) return mod_pow(b, e - 1) * b % MOD;
    else return mod_pow(b * b % MOD, e / 2) % MOD;
}

ll mod_inv(ll x) {
    return mod_pow(x, MOD - 2);
}

ll mod_div(ll n, ll d) {
    return n * mod_inv(d) % MOD;
}

int isectx(int m1, int b1, int m2, int b2) {
    assert(m1 != m2);
    if (m1 < m2) {
        swap(b1, b2);
        swap(m1, m2);
    }
    return (b2 - b1 + m1 - m2 - 1) / (m1 - m2);
}

int eval(int m, int b, int x) {
    return m * x + b;
}

void solve() {
    // reads in inputs
    int n, m;
    cin >> n >> m;

    // gets highest line for each slope (as all others don't matter)
    map<int, int> highest_b_per_m;
    while (n--) {
        int y1, y2;
        cin >> y1 >> y2;
        int slope = (y2 - y1) / m;
        if (!highest_b_per_m.count(slope) || y1 > highest_b_per_m[slope]) {
            highest_b_per_m[slope] = y1;
        }
    }

    // creates convex hull, in the form of segments where each line dominates.
    // interesting implementation note: we do not worry about the intersections going past (to the right of) m,
    // literally at all (while handling the stack for the current line), as we simply remove them all afterward.
    vector<array<int, 3>> segments;
    for (auto [slope, yint] : highest_b_per_m) {
        // pops off all segments that are fully dominated by the current line we are considering
        while (segments.size()) {
            auto [prev_slope, prev_yint, minx] = segments.back();
            int x = isectx(slope, yint, prev_slope, prev_yint);
            if (x <= minx) {
                segments.pop_back();
            } else {
                break;
            }
        }

        // now, pushes the current line onto the stack
        if (segments.size()) {
            auto [prev_slope, prev_yint, minx] = segments.back();
            int x = isectx(slope, yint, prev_slope, prev_yint);
            segments.push_back({slope, yint, x});
        } else {
            segments.push_back({slope, yint, 0});
        }
    }
    while (segments.back()[2] > m) {  // removes any segments past m
        segments.pop_back();
    }
    segments.push_back({-1, -1, m + 1});  // makes a sentinel segment starting at m + 1

    // gets answer for each x value, using convex hull
    vector<int> ans(m + 1);
    for (int i = 0; i < (int) segments.size() - 1; ++i) {
        auto [slope, yint, l] = segments[i];
        auto [_, __, r] = segments[i + 1];
        for (int j = l; j < r; ++j) {
            ans[j] = eval(slope, yint, j);
        }
    }

    // prints out answers
    for (int i = 0; i <= m; ++i) {
        cout << ans[i] << " ";
    }
    cout << "\n";
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
