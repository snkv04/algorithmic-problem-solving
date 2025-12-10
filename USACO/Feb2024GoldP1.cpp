#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
int n, m, c, r, k;
vector<vector<pair<int, ll>>> adj, closest;

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const vector<T> &c) {
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

struct Comp {
    bool operator()(const array<ll, 3> &a, const array<ll, 3> &b) {
        return a[2] > b[2];
    }
};

void solve() {
    cin >> n >> m >> c >> r >> k;
    adj.resize(n);
    while (m--) {
        int a, b, w;
        cin >> a >> b >> w;
        --a; --b;
        adj[a].push_back(make_pair(b, w));
        adj[b].push_back(make_pair(a, w));
    }

    priority_queue<array<ll, 3>, vector<array<ll, 3>>, Comp> pq;
    closest.resize(n);
    for (int i = 0; i < c; ++i) {
        closest[i].push_back(make_pair(i, 0));
        pq.push(array<ll, 3>({i, i, 0}));
    }

    while (pq.size()) {
        auto top = pq.top();
        pq.pop();
        int node = top[0];
        int station = top[1];
        ll dist = top[2];
        // cout << "node = " << node << ", station = " << station << ", dist = " << dist << endl;

        bool done = false;
        for (int i = 0; i < closest[node].size(); ++i) {
            const pair<int, ll> a = closest[node][i];
            if (a.first == station) {
                if (a.second < dist) {
                    done = true;
                }
                break;
            }
        }
        // cout << "done = " << done << endl;
        if (done) continue;

        for (auto next : adj[node]) {
            int next_node = next.first;
            ll weight = next.second;
            if (dist + weight > r) continue;
            ll new_dist = dist + weight;

            bool done = false;
            for (int i = 0; i < closest[next_node].size(); ++i) {
                const pair<int, ll> a = closest[next_node][i];
                if (a.first == station) {
                    if (a.second <= new_dist) {
                        done = true;
                    } else {
                        closest[next_node].erase(
                            remove(closest[next_node].begin(), closest[next_node].end(), a),
                            closest[next_node].end()
                        );
                    }
                    break;
                }
            }
            if (done) continue;

            if (closest[next_node].empty()) {
                closest[next_node].push_back(make_pair(station, new_dist));
                pq.push(array<ll, 3>({next_node, station, new_dist}));
            } else if (closest[next_node].size() == k && closest[next_node].back().second < new_dist) {
                continue;
            } else {
                if (closest[next_node].back().second < new_dist) {
                    closest[next_node].push_back(make_pair(station, new_dist));
                } else {
                    for (int i = 0; i < closest[next_node].size(); ++i) {
                        if (closest[next_node][i].second >= new_dist) {
                            closest[next_node].insert(closest[next_node].begin() + i, make_pair(station, new_dist));
                            break;
                        }
                    }
                }
                if (closest[next_node].size() > k) closest[next_node].pop_back();
                pq.push(array<ll, 3>({next_node, station, new_dist}));
            }
        }
    }

    set<int> ans;
    for (int i = c; i < n; ++i) {
        if (closest[i].size() == k) ans.insert(i+1);
    }

    cout << ans.size() << endl;
    for (int num : ans) cout << num << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
