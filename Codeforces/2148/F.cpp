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
    // justs reads in inputs
    int n;
    cin >> n;
    vector<vector<int>> a(n);
    int maxlen = 0;
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        maxlen = max(maxlen, k);
        while (k--) {
            int aij;
            cin >> aij;
            a[i].push_back(aij);
        }
    }

    // aggregates arrays by length to quickly find which new arrays to consider if scanning right-to-left
    vector<vector<int>> bylength(maxlen);
    for (int i = 0; i < n; ++i) bylength[a[i].size() - 1].push_back(i);

    // precomputes, for each index, the best array if we only use elements at that index or greater
    vector<array<int, 3>> active;
    vector<int> best(maxlen);
    for (int i = maxlen - 1; i >= 0; --i) {
        // activate new arrays and update first element of all active arrays
        // basically, just ensures that `active` is kept up-to-date with current values
        for (int id : bylength[i]) active.push_back({a[id][i], -1, id});
        for (int j = 0; j < active.size(); ++j) {
            active[j][0] = a[active[j][2]][i];
        }
        
        // sort all active arrays by (1) value, (2) rank of all future values, and (3) ID (tiebreaker, doesn't matter)
        sort(active.begin(), active.end());

        // finds best ID using only values at index i or greater
        best[i] = active[0][2];

        // computes new ranks
        for (int rank = 0; rank < active.size(); ++rank) {
            active[rank][1] = rank;
        }
    }

    // jumps through indices, finding best array at index and taking all elements from the best that are >= our index
    vector<int> ans;
    int curr_idx = 0;
    while (curr_idx < maxlen) {
        int best_id = best[curr_idx];
        for (int i = curr_idx; i < a[best_id].size(); ++i) {
            ans.push_back(a[best_id][i]);
        }
        curr_idx = a[best_id].size();
    }
    for (int i = 0; i < maxlen; ++i) cout << ans[i] << " ";
    cout << "\n";
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
