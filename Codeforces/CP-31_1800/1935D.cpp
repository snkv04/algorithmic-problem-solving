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

template <typename T>
std::ostream& operator<<(std::ostream &os, std::set<T> &s) {
    os << "[";
    for (auto s_i : s) os << s_i << ", ";
    os << "]";
    return os;
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

ll num_pairs(ll c) {
    // cout << "num pairs = " << (c + 1) * (c + 2) / 2 << endl;
    return (c + 1) * (c + 2) / 2;
}

ll sum_in_s(set<int> &s) {
    ll result = 0;
    for (int s_i : s) result += s_i / 2 + 1;
    // cout << "num pairs with sum in s = " << result << endl;
    return result;
}

ll diff_in_s(set<int> &s, ll c) {
    ll result = 0;
    for (int s_i : s) result += c + 1 - s_i;
    // cout << "num pairs with difference in s = " << result << endl;
    return result;
}

ll both_in_s(set<int> &s) {
    ll result = 0;
    vector<int> counts(2, 0);
    for (int s_i : s) {
        counts[s_i % 2] += 1;
        result += counts[s_i % 2];
    }
    // cout << "num pairs with both sum and difference in s = " << result << endl;
    return result;
}

void solve() {
    /*
    - problem:
        - find the number of pairs (x, y) such that:
            - they're both nonnegative
            - they're both <= some constant C
            - x is the smaller (or equal) one
            - neither their sum nor difference is in some set S
    - solution:
        - use inclusion-exclusion principle
    - details:
        - to find number of pairs whose sum is in S:
            - iterate through each possible sum S_i in S, and find the number of pairs relatively straightforwardly
            by counting the number of possible x values in O(1)
        - to find number of pairs whose difference is in S:
            - iterate through each possible difference S_i in S, and add up the number of pairs that are
            whose numbers in the pair (so, x and y) are S_i away and they're both in the interval [0, c]
        - to find number of pairs whose sum and difference are both in S:
            - note that if a given S_i is the sum of x and y, then the parity of x and y will either be
            the same across all such pairs or different across all such pairs, and there exists a pair (x, y)
            for each possible difference d where d < S_i and d has that parity
                - proof. for a given S_i, let S_j <= S_i where S_j is congruent to S_i mod 2.
                then we can let (x_base = 0, y_base = S_j).
                then, since S_i is congruent to S_j mod 2, we can set (x = x_base + (Si-Sj)/2, y = y_base + (Si-Sj)/2).
                therefore, x and y are integers, their difference is S_j, and their sum is S_i. qed.
            - also, note that if a given S_i = x + y, then y - x must be <= S_i
            - so, we can iterate through S_i in increasing order, and just keep track of the number of previous
            (including current) S_j where S_j <= S_i and S_j has the same parity as S_i
    */

    int n, c;
    cin >> n >> c;
    set<int> s;
    while (n--) {
        int s_i;
        cin >> s_i;
        s.insert(s_i);
    }
    // cout << "s = " << s << ", c = " << c << endl;
    cout << num_pairs(c) - sum_in_s(s) - diff_in_s(s, c) + both_in_s(s) << endl;
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
