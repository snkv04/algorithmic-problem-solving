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
    vector<pair<int, int>> have(n), additional(m);
    for (int i = 0; i < n + m; ++i) {
        if (i < n) {
            cin >> have[i].second >> have[i].first;
            ++have[i].first;
        } else {
            cin >> additional[i - n].second >> additional[i - n].first;
            ++additional[i - n].first;
        }
    }
    sort(have.begin(), have.end());
    // cout << "have = " << have << endl;
    // cout << "additional = " << additional << endl;

    // initializes set of available and taken items
    multiset<int> available, taking;
    ll takingsum = 0;
    for (int i = 0; i < n; ++i) {
        available.insert(have[i].second);
    }

    // gets info about which items we take, assuming we're taking t items (or less!)
    vector<ll> bestsum(n + 2, 0), minelem(n + 2, 0);
    int leftidx = 0;
    for (int t = 1; t <= n + 1; ++t) {
        while (leftidx < n && have[leftidx].first < t) {
            ll value = have[leftidx].second;
            if (taking.find(value) != taking.end()) {
                takingsum -= value;
                taking.erase(taking.find(value));

                if (available.size()) {
                    ll newvalue = *available.rbegin();
                    available.erase(available.find(newvalue));
                    taking.insert(newvalue);
                    takingsum += newvalue;
                }
            } else {
                assert(available.find(value) != available.end());
                available.erase(available.find(value));
            }
            ++leftidx;
        }

        if (available.size()) {
            ll best = *available.rbegin();
            available.erase(available.find(best));
            taking.insert(best);
            takingsum += best;
        }

        bestsum[t] = takingsum;
        if (taking.size() == t) {
            minelem[t] = *taking.begin();
        }  // else, don't have to remove anything
    }

    // for each t, assume we were going to take t items but removed the lowest-value one (so we could replace it
    // with the one we buy), and the new sum is (bestsum[t] - minelem[t])
    // then, among all t where t <= constraint(new item), we take the max of that above (bestsum[t] - minelem[t])
    // value and add it to the new item's value
    ll best_overall = 0;
    vector<ll> if_removed_pref(n + 2, 0);
    for (int t = 1; t <= n + 1; ++t) {
        best_overall = max(best_overall, bestsum[t]);
        if_removed_pref[t] = max(if_removed_pref[t - 1], bestsum[t] - minelem[t]);
    }

    // now, finds the best value if we have each new item available
    for (auto [y, x] : additional) {
        ll ans = max(
            best_overall,
            x + if_removed_pref[min(n + 1, y)]
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
