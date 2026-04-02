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
        - we have an infinite-vertex graph, where there is a directed edge from u to (u + v) if and only if
        (u AND v) = v
        - given a bunch of queries, where each query specifies a start and end vertex, is it possible
        to reach the end vertex from the start?
    - solution:
        - important observation: for a (u -> u + v) operation to be valid, the bits of v must be a subset of
        the bits of u
        - then, each individual (u -> u + v) operation can be thought of as moving bits to the left and/or
        deleting bits, due to the carry-over logic of addition
        - so, a sequence of operations (i.e., a directed path) can be thought of as the same thing
        - therefore, we just need to make sure that for every prefix of bits, there are more bits in u
        than in v
    - details:
        - why check prefixes (where "start" is assumed to be LSB) and not suffixes? basically, we just want
        each bit in v to come from somewhere in the LSB direction from u. we can also do a 2 pointer approach,
        to match each bit in v to a bit in u, going from MSB to LSB. it just so happens that checking to make
        sure every prefix sum is nonnegative also works, where we get +1 from a bit in u and -1 from a bit in v.
        - it happens to be the case that each individual (u -> u + v) operation can be separated into individual
        bit additions, breaking down the given operation even further. a single bit addition has the straightforward
        carry-over logic, so this can be helpful. however, this information is not really necessary for this problem;
        the important part is that each individual edge just deletes/shifts left some bits from the start node
        of that edge.
            - just in case it's helpful for future problems: suppose we add bits {b_1, b_2, ..., b_k} from v to u.
            each of those bits is has a 1 in the corresponding slot, by the way. let b_1 > b_2 > ... > b_k.
            also, let bits b_1 through b_k be consecutive; if they're not, then we can partition it into sets
            that are. then since addition is commutative, we can think about this addition in 2 main ways:
                - we add b_k, which will carry over across the entire contiguous block, then we add b_{k-1},
                which turns one of the just-turned-off bits back on, then we add b_{k-2}, which does the same
                thing, etc. up to b_1. in this view, the bits affected in the domino effect of adding b_k
                overlap with the bits affected when adding b_1.
                - we add b_1, which will push a bit to the left by carrying over. then we add b_2, which will push
                a bit to the left by carrying over. on and on. in this view, the bits affected when adding b_i
                only overlap with the bits affected when adding b_{i-1} and b_{i+1}.
            so probably the second one, which just goes left-to-right, is simpler to think about.
    */

    int u, v;
    cin >> u >> v;
    if (v < u) {
        cout << "NO\n";
        return;
    }

    int i = 0, pref = 0;
    while (i < 30) {
        int power = 1 << i;
        int ubit = power & u, vbit = power & v;

        if (ubit) ++pref;
        if (vbit) --pref;

        if (pref < 0) {
            cout << "NO\n";
            return;
        }
        ++i;
    }
    cout << "YES\n";
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
