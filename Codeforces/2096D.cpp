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

set<pair<int, int>> shift(set<pair<int, int>> &coords) {
    set<pair<int, int>> result;
    for (auto [x, y] : coords) result.insert(make_pair(x, y + x));
    return result;
}

pair<int, int> find(set<pair<int, int>> &coords) {
    map<int, int> xcnt, ycnt;
    for (auto [x, y] : coords) {
        xcnt[x] += 1;
        ycnt[y] += 1;
    }

    int ansx, ansy;
    for (auto [k, v] : xcnt) if (v % 2) {
        ansx = k;
        break;
    }
    for (auto [k, v] : ycnt) if (v % 2) {
        ansy = k;
        break;
    }
    return make_pair(ansx, ansy);
}

pair<int, int> unshift(pair<int, int> &p) {
    return make_pair(p.first, p.second - p.first);
}

void solve() {
    /*
    - problem:
        - we start with a single (x, y) that is turned on
        - in a single operation, we can flip all lightbulbs in a tetris "S" shape (with the rotation fixed)
        - we are given the end state after doing a bunch of operations; what is one possible initial state?
    - solution:
        - shift all coordinates so that instead of having every operation take place on a tetris "S", they take
        place on a tetris square
        - observe the invariant property of the square operation that every column's number of turned-on lightbulbs
        retains the same parity, and every row's number of turned-on lightbulbs retains the same party; so, just
        find the row and col with an even parity of lightbulbs
        - then, unshift all coordinates to bring them back to the problem space
    - useful ideas:
        - ask myself, "can we map the given set of values with the given set of operations into a different set
        of values with a simpler set of operations, where there's a mapping (ideally a bijection) between the
        answers to the two problems?"
        - there are other interesting properties of the square operation, such as "1 lightbulb in the square always
        turns into 3", "3 -> 1", "2 -> 2", etc., but it happens that those properties are not directly important
        for solving the problem. the most important invariant is that the parity of the number of lightbulbs in
        any given row (y-value) and any given column (x-value) stays fixed
        - another way to solve the problem, as given in the editorial, is to observe that instead of using a square
        operation and observing the invariant parity of each row and column, we can use the given operation and
        observe the invariant parity of each column and down-right diagonal
    */

    int n;
    cin >> n;
    set<pair<int, int>> coords;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        coords.insert(make_pair(x, y));
    }

    coords = shift(coords);
    pair<int, int> ans = find(coords);
    ans = unshift(ans);
    cout << ans.first << " " << ans.second << "\n";
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
