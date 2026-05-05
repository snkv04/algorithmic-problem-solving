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
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> have(n), others(m);
    for (int i = 0; i < n; ++i) {
        cin >> have[i].second >> have[i].first;
        ++have[i].first;
    }
    for (int i = 0; i < m; ++i) {
        cin >> others[i].second >> others[i].first;
        ++others[i].first;
    }
    sort(have.begin(), have.end());

    // why bother going in decreasing order for our "number of items being taken" variable?
    // because if we increase it, then we gradually reduce our number of options. that can make
    // the code complicated, especially if we're maintaining multiple sets. if we decrease it,
    // we gradually increase our number of options (items we can take whose constraints are
    // compliant with the number of items we're taking), and the code is cleaner when adding
    // new options into our multiset.
    multiset<int> taking;
    ll takingsum = 0;
    vector<ll> bestsum(n + 2, 0), minelem(n + 2, 0);
    int idx = n;
    for (int i = n + 1; i >= 1; --i) {
        // adds in new options
        while (idx - 1 >= 0 && have[idx - 1].first >= i) {
            --idx;
            taking.insert(have[idx].second);
            takingsum += have[idx].second;
        }

        // removes options until we are taking <= i items
        while (taking.size() > i) {
            takingsum -= *taking.begin();
            taking.erase(taking.begin());
        }

        // updates best sum and element to remove if we're taking <= i items
        bestsum[i] = takingsum;
        if (taking.size() == i) {
            minelem[i] = *taking.begin();
        }  // else, minelem[i] == 0, meaning that we don't have to remove anything
    }

    ll best = 0;
    vector<ll> pref(n + 2, 0);
    for (int i = 1; i <= n + 1; ++i) {
        best = max(best, bestsum[i]);
        pref[i] = max(pref[i - 1], bestsum[i] - minelem[i]);
    }

    for (auto [constraint, value] : others) {
        ll ans = max(
            best,
            value + pref[constraint]
        );
        cout << ans << " ";
    }
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
