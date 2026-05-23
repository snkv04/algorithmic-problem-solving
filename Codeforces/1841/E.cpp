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

void solve() {
    // reads in inputs
    int n;
    cin >> n;
    vector<int> a(n + 2, n);
    map<int, set<int>> events;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        events[a[i]].insert(i);
    }
    ll m;
    cin >> m;
    if (!m) {
        cout << "0\n";
        return;
    }

    // finds count for each segment length
    map<ll, ll> len_cnt;
    map<int, int> curr_segments;
    for (auto [k, v] : events) {
        if (k == n) break;

        // gets all new segments, where a new segment might require processing multiple bars at different indices
        // in order to be constructed
        map<int, int> new_segments;
        for (int idx : v) {
            // creates segment
            pair<int, int> segment = {idx, idx};

            // checks left and right within existing segments
            if (curr_segments.lower_bound(segment.first) != curr_segments.begin()) {
                auto it = curr_segments.lower_bound(segment.first);
                --it;
                if (it->second == segment.first - 1) {
                    segment.first = it->first;
                    curr_segments.erase(it);
                }
            }
            if (curr_segments.upper_bound(segment.first) != curr_segments.end()) {
                auto it = curr_segments.upper_bound(segment.first);
                if (it->first == segment.second + 1) {
                    segment.second = it->second;
                    curr_segments.erase(it);
                }
            }

            // checks left and right within newly-created segments at this same height
            if (new_segments.lower_bound(segment.first) != new_segments.begin()) {
                auto it = new_segments.lower_bound(segment.first);
                --it;
                if (it->second == segment.first - 1) {
                    segment.first = it->first;
                    new_segments.erase(it);
                }
            }
            if (new_segments.upper_bound(segment.first) != new_segments.end()) {
                auto it = new_segments.upper_bound(segment.first);
                if (it->first == segment.second + 1) {
                    segment.second = it->second;
                    new_segments.erase(it);
                }
            }

            // adds into new segments
            new_segments.insert(segment);
        }

        // for each new segment:
        // - finds last height that this segment, on its own (meaning without being transformed by being extended),
        // will exist
        // - adds it into current segments
        for (auto [l, r] : new_segments) {
            int end = min(a[l - 1], a[r + 1]);
            int cnt = end - k;
            len_cnt[r - l + 1] += cnt;
            curr_segments.insert({l, r});
        }
    }

    // gets answer by simply greedily taking longest
    ll used_segments = 0, remaining_cells = m;
    for (auto it = len_cnt.rbegin(); it != len_cnt.rend() && remaining_cells; ++it) {
        ll len = it->first, cnt = it->second;
        if (len * cnt >= remaining_cells) {
            used_segments += (remaining_cells + len - 1) / len;
            remaining_cells = 0;
        } else {
            used_segments += cnt;
            remaining_cells -= len * cnt;
        }
    }
    cout << m - used_segments << "\n";
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
