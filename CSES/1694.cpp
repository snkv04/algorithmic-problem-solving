#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
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

template <typename T1, typename T2>
std::istream& operator>>(std::istream &is, std::pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
    }
    return is;
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

struct Edge {
    int v;
    ll c, f;
    Edge *rev;
};

struct Dinics {
    static const int inf = 1e9, MAXN=505;
    int n;
    vector<Edge*> e[MAXN], e1[MAXN];
    int dep[MAXN];
    bool mark[MAXN];

    Dinics(int n) : n(n) {}
    
    bool bfs_level(int s, int t) {
        fill(dep, dep+n, -1);
        for (int u = 0; u < n; ++u) {
            e1[u].clear();
        }
        queue<int> q;
        q.push(s);
        dep[s] = 0;
        while (q.size()) {
            int u = q.front();
            q.pop();
            if (u == t) return 1;

            for (int i = 0; i < e[u].size(); ++i) {
                Edge *uv = e[u][i];
                int v = uv->v;
                ll c = uv->c, f = uv->f;
                if (f < c) {
                    if (dep[v] == -1) {
                        dep[v] = dep[u] + 1;
                        q.push(v);
                    }
                    if (dep[v] == dep[u] + 1) {
                        e1[u].push_back(uv);
                    }
                }
            }
        }
        return 0;
    }

    ll dfs_flow(int u, int t, ll dt) {
        if (u == t) return dt;
        ll tot = 0;
        for (int i = 0; i < e1[u].size(); ++i) {
            Edge *uv = e1[u][i];
            int v = uv->v;
            ll c = uv->c, f = uv->f;
            if (!mark[v] && f < c) {
                ll vdt = dfs_flow(v, t, min(c-f, dt-tot));
                if (vdt > 0) {
                    uv->f += vdt;
                    uv->rev->f -= vdt;
                    tot += vdt;
                }
            }
        }
        
        if (tot == 0) mark[u] = 1;
        return tot;
    }

    ll run(int s, int t) {
        for (int u = 0; u < n; ++u) {
            for (int i = 0; i < e[u].size(); ++i) {
                e[u][i]->f = 0;
            }
        }

        ll res = 0;
        while (bfs_level(s, t)) {
            fill(mark, mark+n, false);
            res += dfs_flow(s, t, inf);
        }
        return res;
    }

    void add_edge(int u, int v, ll c) {
        Edge *edge = new Edge{v, c, 0, nullptr};
        Edge *rev = new Edge{u, 0, 0, edge};
        edge->rev = rev;
        e[u].push_back(edge);
        e[v].push_back(rev);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    Dinics d(n + 1);
    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        d.add_edge(a, b, c);
    }
    cout << d.run(1, n) << endl;
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
