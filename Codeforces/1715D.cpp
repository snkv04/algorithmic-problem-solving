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
        - we're given the size of an array and a bunch of constraints saying that a pair of element's OR value
        is equal to some value
        - construct the lexicographically smallest array fitting the constraints
    - solution:
        - we can do this bit by bit, because constraints on particular bits are completely independent from
        other bits; therefore, each constraint either says the OR is 0 or it's 1
        - if a constraint says that the OR is 0, then both of those elements are simply fixed at 0
        - if a constraint says that the OR is 1, then:
            - if one of them is fixed at 0, then the other is fixed at 1
            - otherwise, at least one of them has to be 1. we want to lexicographically minimize the array, so
            we want leftmost elements to be 0 if possible. to achieve this, we use very simple logic:
                - iterate from left to right
                - if something hasn't been fixed, then fix it to 0
                - process adjacent constraints, which may/may not fix future elements
    - generalized ideas for the future:
        - ad hoc problems, or maybe all problems in general, really just come down to laying out all of
        the known information clearly, then repeatedly drawing conclusions from that
    */

    int n, q;
    cin >> n >> q;

    vector<array<int, 3>> constraints(q);
    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < 3; ++j) cin >> constraints[i][j];
        --constraints[i][0]; --constraints[i][1];
        if (constraints[i][0] > constraints[i][1]) swap(constraints[i][0], constraints[i][1]);
    }

    vector<int> a(n, 0);
    for (int b = 0; b < 30; ++b) {
        // fix all 0-pair elements to 0
        vector<vector<int>> adj(n);
        vector<int> a_b(n, -1);
        for (auto [i, j, x] : constraints) {
            if (((x >> b) & 1) == 0) {
                a_b[i] = a_b[j] = 0;
            }
        }

        // fix all 1-pair elements, where one of the two is set to 0, to 1
        for (auto [i, j, x] : constraints) {
            if ((x >> b) & 1) {
                if (i == j) {
                    a_b[i] = 1;
                } else if (a_b[i] == 0) {
                    a_b[j] = 1;
                } else if (a_b[j] == 0) {
                    a_b[i] = 1;
                } else {
                    adj[i].push_back(j);
                }
            }
        }

        // walk through rest of elements. if unfixed, then fix to 0. then, process adjacent constraints.
        for (int i = 0; i < n; ++i) {
            // if it hasn't been forced into being set to any value, set it to 0
            if (a_b[i] == -1) {
                a_b[i] = 0;
            }

            if (a_b[i] == 0) {
                // if this is 0, then all adjacent elements must be 1
                for (auto j : adj[i]) {
                    a_b[j] = 1;
                }
            } /* else {
                // if this is 1, then we'd like for adjacent elements to be 0, but:
                // - if they're already 0, then we don't need to do anything
                // - if they're already forced to be 1, then we can't bring them down to 0
                // so we only set them to 0 if they haven't been set.
                //
                // ...but it turns out that this entire branch is unnecessary. we will set
                // unset elements to 0 anyway.
                for (auto j : adj[i]) {
                    if (a_b[j] == -1) {
                        a_b[j] = 0;
                    }
                }
            } */
        }

        // cout << "b = " << b << ", a_b = " << a_b << endl;
        for (int i = 0; i < n; ++i) a[i] += (1 << b) * a_b[i];
    }
    
    for (int i = 0; i < n; ++i) cout << a[i] << ' ';
    cout << '\n';
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
