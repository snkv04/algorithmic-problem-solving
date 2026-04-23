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
    - useful ideas:
        - if we always assign the minimum possible not-currently-using room to a segment, then the total
        number of rooms used will be equal to the maximum number of overlapping segments across all points
        in time
    */

    int n;
    cin >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; ++i) cin >> l[i] >> r[i];

    // coordinate compression for times
    map<int, int> times;
    for (int i = 0; i < n; ++i) {
        times[l[i]] = -1;
        times[r[i]] = -1;
    }
    int t = 0;
    for (auto it = times.begin(); it != times.end(); ++it) {
        it->second = t++;
    }
    vector<vector<int>> joining(times.size()), leaving(times.size());
    for (int i = 0; i < n; ++i) {
        joining[times[l[i]]].push_back(i);
        leaving[times[r[i]]].push_back(i);
    }

    set<int> available;
    for (int i = 1; i <= n; ++i) available.insert(i);
    
    vector<int> assigned(n, -1);
    int curr_using = 0, ans = 0;
    for (t = 0; t < times.size(); ++t) {
        for (int arriving : joining[t]) {
            int room = *available.begin();
            available.erase(room);
            assigned[arriving] = room;
            ++curr_using;
            ans = max(ans, curr_using);
        }

        for (int departing : leaving[t]) {
            int room = assigned[departing];
            available.insert(room);
            --curr_using;
        }
    }

    cout << ans << endl;
    for (int i = 0; i < n; ++i) cout << assigned[i] << " ";
    cout << endl;
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
