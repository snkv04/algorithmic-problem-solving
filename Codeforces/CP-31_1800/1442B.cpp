#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 998244353;
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
    - literally just a logic puzzle. lay out the known information clearly, then repeatedly draw conclusions from it.
    - solution:
        - for a given value of b_i, either the element to the left or to the right in a is removed. let's look at cases:
            - one of them appear as future values in b. then, the other one has to be removed, because if that first
            one was removed, then having it appear again in b is a conradiction
            - both of them appear as future values in b. that's already a contradiction; it's not possible to remove
            either of them, because we have information saying that they will both appear later
            - neither of them appear as future values in b. then, since b_i also never appears again (since all elements
            of b are distinct), all three of those neighboring values are now just no-name NPCs that are free to be
            used as remove-dummies for later. so, we just arbitrarily remove one of them, note that there are 2 possible
            choices (and this "noting" is done by multiplying the number of possible sequences by 2), and move on
        - so, our final answer will keep multiplying by 1 or 2, or drop to 0
    - useful ideas for the future:
        - a random fact in the problem whose importance is unclear can come in clutch, so make sure to reread the problem.
        the fact that b can only consist of distinct elements makes this problem 100x easier.
        - the number of possible sequences is computed by multiplying the number of possibilities that each element
        of b provides
    */

    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(k);
    cin >> a >> b;
    for (int i = 0; i < n; ++i) --a[i];
    for (int i = 0; i < k; ++i) --b[i];

    vector<int> inv(n);
    for (int i = 0; i < n; ++i) inv[a[i]] = i;
    for (int i = 0; i < k; ++i) b[i] = inv[b[i]];

    vector<int> rightmost(n, -1);
    for (int i = 0; i < k; ++i) {
        rightmost[b[i]] = i;
    }

    set<int> remaining;
    for (int i = 0; i < n; ++i) remaining.insert(i);
    int ans = 1;
    for (int i = 0; i < k; ++i) {
        int val = b[i];

        vector<int> possible;
        auto it = remaining.upper_bound(val);
        if (it != remaining.end()) possible.push_back(*it);
        it = remaining.lower_bound(val);
        if (it != remaining.begin()) possible.push_back(*(--it));

        for (int j = possible.size() - 1; j >= 0; --j) {
            if (rightmost[possible[j]] > i) {
                possible.erase(possible.begin() + j);
            }
        }

        if (possible.empty()) {
            cout << "0\n";
            return;
        } else if (possible.size() == 1) {
            remaining.erase(possible[0]);
        } else {
            ans = (2 * ans) % MOD;
            remaining.erase(possible[0]);
        }
    }
    cout << ans << endl;
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
