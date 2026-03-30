#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
constexpr ll INF = 1e12, NEG_INF = -1e12;
ll m, x, sum;
vector<ll> c, h;

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

void solve_by_max_money() {
    // let mem[i][j] := maximum money we still have if we are on day i (without having had received the money
    // for day i) and have obtained j happiness
    vector<vector<ll>> mem(m, vector<ll>(sum + 1, NEG_INF));
    mem[0][0] = 0;
    if (c[0] == 0) mem[0][h[0]] = 0;  // we can't buy anything on the first day, unless the cost is 0
    for (int i = 1; i < m; ++i) {
        for (int j = 0; j <= sum; ++j) {
            // if we don't buy anything, then we simply gain x money
            if (mem[i - 1][j] != NEG_INF) mem[i][j] = max(mem[i][j], mem[i - 1][j] + x);

            // if we do buy something, then we gain x money, lose c[i] money, and gain h[i] happiness
            if (j >= h[i] && c[i] <= mem[i - 1][j - h[i]] + x) {
                mem[i][j] = max(mem[i][j], mem[i - 1][j - h[i]] + x - c[i]);
            }
        }
    }

    // finds the maximum happiness such that it is possible to get that much happiness after all the days
    int ans = 0;
    for (int i = sum; i > 0; --i) if (mem[m-1][i] >= 0) { ans = i; break; }
    cout << ans << '\n';
}

void solve_by_min_cost() {
    // mem[i][j] := minimum cost such that we are on day i and have obtained happiness j, and we've never
    // allowed our cost to exceed our total money gained
    vector<vector<ll>> mem(m, vector<ll>(sum + 1, INF));
    mem[0][0] = 0;
    if (!c[0]) mem[0][h[0]] = 0;
    for (int i = 1; i < m; ++i) {
        ll money_made = i * x;
        for (int j = 0; j <= sum; ++j) {
            // if we don't buy it, then our cost hasn't changed
            if (mem[i - 1][j] != INF) {
                mem[i][j] = min(mem[i][j], mem[i - 1][j]);
            }

            // if we do buy it, then our cost increases by c[i] and our happiness increases by h[i]
            if (j >= h[i] && mem[i - 1][j - h[i]] + c[i] <= money_made) {
                mem[i][j] = min(mem[i][j], mem[i - 1][j - h[i]] + c[i]);
            }
        }
    }

    // finds maximum happiness such that it is possible to get that much happiness after all the days
    int ans = 0;
    for (int i = sum; i > 0; --i) if (mem[m-1][i] < INF) { ans = i; break; }
    cout << ans << '\n';
}

void solve() {
    /*
    - problem:
        - on each day, we gain some fixed amount of money, and have a choice to either buy or not buy
        something for some cost to get some happiness
        - what's the max happiness we can get, without ever making our money go into the negatives?
        - and by the way, the number of days and the max amount of happiness is small, while the costs
        and amount of money we make are large
    - solution:
        - on each day, the only two things that matter are how much happiness we've had so far and how
        much money we still have; so, we define mem[i][j] as the maximum amount of money we can make
        by day i if we've gained j happiness
        - then, we compute our transitions by either buying (if possible) or not buying the object on
        each day
    - details:
        - alternatively, we can compute the minimum cost for each (i, j), since the amount of money we
        will have made on day i is fixed
            - in both variations, the additional assumption is that we reach state (i, j) without having
            ever dropped below 0 money, though that's kind of already known and implied
    */

    // reads in the input
    cin >> m >> x;
    c = vector<ll>(m); h = vector<ll>(m);
    sum = 0;
    for (int i = 0; i < m; ++i) { cin >> c[i] >> h[i]; sum += h[i]; }

    // solve_by_max_money();
    solve_by_min_cost();
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
