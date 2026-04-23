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

struct Comparator {
    static bool operator()(const array<int, 3> &a, const array<int, 3> &b) {
        if (a[1] != b[1]) {
            return a[1] < b[1];  // left bound, increasing order
        } else {
            return a[2] > b[2];  // right bound, decreasing order
        }
    }
};

void solve() {
    int n;
    cin >> n;
    vector<array<int, 3>> segments(n);
    for (int i = 0; i < n; ++i) {
        segments[i][0] = i;
        cin >> segments[i][1] >> segments[i][2];
    }
    sort(segments.begin(), segments.end(), Comparator::operator());  // can use struct, just make 

    vector<bool> is_contained(n, false), contains(n, false);
    set<int> rights;
    for (int i = 0; i < n; ++i) {
        auto [idx, l, r] = segments[i];
        if (rights.lower_bound(r) != rights.end()) {
            // there is some previously-processed [l_j, r_j] where l_j <= l is guaranteed
            // and we also now know that r_j >= r, so [l, r] is contained
            is_contained[idx] = true;
        }
        rights.insert(r);
    }
    rights.clear();
    for (int i = n - 1; i >= 0; --i) {
        auto [idx, l, r] = segments[i];
        if (rights.size() && *rights.begin() <= r) {
            // we know that all previously-processed [l_j, r_j] have l_j >= l,
            // and we now also know that there's some r_j <= r
            contains[idx] = true;
        }
        rights.insert(r);
    }

    for (int i = 0; i < n; ++i) cout << static_cast<int>(contains[i]) << " ";
    cout << "\n";
    for (int i = 0; i < n; ++i) cout << static_cast<int>(is_contained[i]) << " ";
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
