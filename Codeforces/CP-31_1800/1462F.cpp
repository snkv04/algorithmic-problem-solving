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
    // reads in input
    int n;
    cin >> n;
    vector<vector<int>> segments(n, vector<int>(2, 0));
    for (int i = 0; i < n; ++i) cin >> segments[i];

    // maps each right-side value to the number of segments whose right-side value is there or to the left,
    // and maps each left end to the number of segments whose left end is there or to the right
    map<int, int> left, right;
    for (int i = 0; i < n; ++i) {
        left[segments[i][1]] += 1;
        right[segments[i][0]] += 1;
    }
    int pref = 0;
    for (auto it = left.begin(); it != left.end(); ++it) {
        it->second += pref;
        pref = it->second;
    }
    int suf = 0;
    for (auto it = right.rbegin(); it != right.rend(); ++it) {
        it->second += suf;
        suf = it->second;
    }

    // iterates through each segment that could be the universally-intersecting segment
    int ans = 1e9;
    for (int i = 0; i < n; ++i) {
        int nonoverlapping = 0;
        
        auto it = left.lower_bound(segments[i][0]);
        if (it != left.begin()) {
            --it;
            nonoverlapping += it->second;
        }

        auto it2 = right.upper_bound(segments[i][1]);
        if (it2 != right.end()) {
            nonoverlapping += it2->second;
        }

        ans = min(ans, nonoverlapping);
    }
    cout << ans << '\n';
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
