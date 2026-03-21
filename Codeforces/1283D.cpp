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
    // places all trees into a set
    int n, m;
    cin >> n >> m;
    set<ll> x;
    while (n--) {
        int xi;
        cin >> xi;
        x.insert(xi);
    }
    
    // schedules initial nodes at distance 1
    queue<pair<ll, ll>> q;
    for (int xi : x) {
        if (x.find(xi-1) == x.end()) {
            q.push(make_pair(xi-1, 1));
        }
        if (x.find(xi+1) == x.end()) {
            q.push(make_pair(xi+1, 1));
        }
    }

    // core idea: we process nodes in order of increasing distance with BFS
    ll ans = 0;
    vector<ll> positions;
    set<ll> visited;
    while (m) {
        auto [pos, dist] = q.front();
        q.pop();
        if (visited.find(pos) != visited.end()) continue;

        visited.insert(pos);
        positions.push_back(pos);
        ans += dist;
        --m;

        vector<ll> next = {pos - 1, pos + 1};
        for (int nextpos : next) {
            if (visited.find(nextpos) == visited.end() && x.find(nextpos) == x.end()) {
                ll nextdist = 1e12;
                auto it = x.lower_bound(nextpos);
                if (it != x.begin()) {
                    --it;
                    nextdist = min(nextdist, nextpos - *it);
                }
                it = x.upper_bound(nextpos);
                if (it != x.end()) {
                    nextdist = min(nextdist, *it - nextpos);
                }
                q.push(make_pair(nextpos, nextdist));
            }
        }
    }

    // outputs answers
    cout << ans << '\n';
    for (auto pos : positions) cout << pos << ' ';
    cout << '\n';
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
