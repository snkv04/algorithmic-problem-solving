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

void solve() {
    /*
    key ideas:
    - when we maximize one thing, it's usually the case that we're also trying to minimize something else
    - if we reframe it as having each connected streak of points be a "subarray" or "segment", then this
    problem becomes very similar to https://codeforces.com/problemset/problem/1992/F, in that we are trying
    to minimize the number of subarrays that we partition our main array into
    - we do it greedily, because: for a given subarray, the longer we make it go, the more restrictions it
    has. so, if we have the option of starting our second subarray sooner or later, we make the first one
    go longer and start the second one as late as possible.
    */

    int n;
    cin >> n;
    vector<ll> x(n);
    cin >> x;
    if (n == 1) {
        cout << "0\n";
        return;
    }
    x.insert(x.begin(), -1e15);
    x.push_back(1e15);

    ll l = 0, r = min(x[2] - x[1], x[1] - x[0]), splits = 0;
    for (int i = 2; i <= n; ++i) {
        ll prevl = x[i] - x[i - 1] - r, prevr = x[i] - x[i - 1] - l;
        ll currl = 0, curr_r = min(x[i + 1] - x[i], x[i] - x[i - 1]);
        l = max(prevl, currl);
        r = min(prevr, curr_r);

        // interval must be non-empty, with open bounds
        if (l >= r) {
            ++splits;
            l = currl;
            r = curr_r;
        }
    }
    cout << n - 1 - splits << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
