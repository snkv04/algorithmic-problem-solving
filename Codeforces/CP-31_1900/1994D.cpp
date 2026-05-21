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
        - we have a graph with n nodes and no edges. each node i has an associated value a_i.
        - we want to perform (n - 1) operations, where on the i'th operation, we join two nodes whose
        difference in a_i values is divisible by i
            - so on operation 1, we join up i and j such that |a_i - a_j| is divisible by 1, on operation
            2, we join up i and j such that |a_i - a_j| is divisible by 2, etc.
        - is it possible to make a tree?
    - solution:
        - from the example cases, it is implied that it might always be possible; it is, in fact, always possible
        - key observation: by the pigeonhole principle, for a set of n numbers, we can always find a pair of them
        whose difference is divisible by (n-1)
            - proof. we have that two numbers x and y are such that d divides |x - y| if x % d == y % d. then,
            if we have n integers, then there are (n-1) possible values for the modulo of each to fall into, and
            then one such modulo value must contain two such integers. as a result, those two such integers
            will have their difference divisible by n-1. qed.
        - as a result, we can start with n elements, find a pair whose difference is divisible by (n-1),
        remove one of those elements, then keep doing it until we only have 1 element
            - by doing this, all nodes are connected to each other; this is easily proven by looking backwards:
            the last element is connected to the second to last one, the last 2 are connected to the 3rd to last one,
            the last 3 are connected to the 4th to last one, etc.
            - quick sanity check: if there are only 2 elements, then of course their difference will be divisible
            by 1, because all integers (which is what their difference will be) are divisible by 1
    - generalized ideas for the future:
        - how to quickly come up with this idea again?
            - first, observe that since we only have n-1 edges to place, each one needs to connect two unconnected
            nodes. we can force this by making each component only have a single node available for future pairs,
            meaning that when we connect 2 nodes, 1 of them does not get processed again.
            - we can either think about {starting from operation index, then looking at what pairs of nodes we
            can use for each operation} or {starting from available pairs of nodes, then looking at how to order
            our operations by applying the operations to these pairs}. we can choose the first one arbitrarily.
            - we can either think about the operations going forward or backward. if we go forward, then we limit
            the nodes we need for larger divisors. or, we can go backward, and start with larger divisors (operation
            indices) first. the latter seems better.
            - now, for an operation index i, observe that we have i+1 nodes available. then, we can find that it's
            actually ALWAYS possible to make a pair, then remove that node in preparation for smaller divisors.
            - the remaining ideas in the algorithm are trivial: we find two elements whose difference is divisible by
            d in O(n), for an O(n^2) solution.
    */

    // reads in input
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    // finds a pair for each i \in [1, n - 1], and removes one of those elements (either one works,
    // because as long as there are ANY i elements remaining, we can find a pair whose difference
    // is divisible by (i-1), by the pigeonhole principle)
    vector<pair<int, int>> ans;
    vector<bool> used(n, false);
    for (int i = n - 1; i >= 1; --i) {
        map<int, int> mod_to_idx;
        for (int j = 0; j < a.size(); ++j) {
            if (used[j]) continue;

            if (mod_to_idx.find(a[j] % i) == mod_to_idx.end()) {
                mod_to_idx[a[j] % i] = j;
            } else {
                ans.push_back(make_pair(mod_to_idx[a[j] % i], j));
                used[j] = true;
                break;
            }
        }
    }

    // reverses the pairs found and outputs them
    cout << "YES\n";
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < n - 1; ++i) {
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << "\n";
    }
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
