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
    - problem:
        - we have an array of length up to 2e3
        - suppose we can reorder it however we want. what is the minimum value of
        (sum across i of (prefix max up to index i minums prefix min up to index i))?
    - solution:
        - key observation: suppose our prefix i consists of i numbers. then the (i+1)th number in the array
        should not be strictly within the minimum and maximum of the prefix up to index i, because if it was,
        then we unnecessarily have a large difference too early and can delay it
            - in other words, our selection of elements will keep moving "outward"
            - it's NOT like we're zigzagging, or spiraling, from our first element
            to the right of all selected so far
            to the left of all selected so far
            to the right of all selected so far
            etc. the "constantly moving outward" logic is more general than this, and so the zigzag logic is
            just a particular instance. the reason why zigzagging is incorrect is that it sometimes is correct
            to keep moving in one direction instead of switching. for example, [1, 3, 3, 3, 6, 6]. it's best
            to go in the order [3, 3, 3, 6, 6, 1], but a zigzag would force us to suboptimally switch directions.
        - then, we can do DP, where mem[i][j] is equal to the minimum cost of having selected the numbers in
        index range [i, j] so far, and we compute it by either having the last element in that interval be
        s[i] or s[j]
    */

    // reads in the input and sorts the array
    int n;
    cin >> n;
    vector<int> s(n);
    cin >> s;
    sort(s.begin(), s.end());

    // runs a simple DP
    vector<vector<ll>> mem(n, vector<ll>(n, 1e15));
    for (int i = 0; i < n; ++i) mem[i][i] = 0;
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len <= n; ++i) {
            int j = i + len - 1;
            mem[i][j] = min(mem[i+1][j] + s[j] - s[i], mem[i][j-1] + s[j] - s[i]);
        }
    }
    cout << mem[0][n-1] << endl;
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
