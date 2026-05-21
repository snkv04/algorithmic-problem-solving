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
    - solution:
        - let's simplify the problem to a single bit. for fixed y, we want to find num of pairs (x, z) where
        x<=y<=z and f(x,z) XOR a_y > f(x, z). observe that:
            - if a_y == 0, then f(x,z) == f(x, y) XOR f(y, z) no matter what x and z are
            - if a_y == 1, then f(x, y) XOR f(y, z) > f(x, z) if count of 1s in [x, z] is even, and
                                f(x, y) XOR f(y, z) < f(x, z) otherwise.
            we of course want the first case.
        - now let's move to multiple bits. let y be fixed. we want to find num of valid pairs (x, z). take a
        look at an arbitrary bit i:
            - let's denote f_i(a, b) as f(a, b) only operating on bit i. then f(a, b) = sum over i of f_i(a, b).
            - so we can observe that if f_j(x,y) XOR f_j(y,z) > f_j(x,z) for ANY j>i, then no matter how much
            we subtract, we can't change that
            - similarly, if f_j(x,y) XOR f_j(y,z) < f_j(x,z) for ANY j>i, then no matter how much we add on these
            lower bits, we can't change that
            - so, all bits i lower than MSB are useless to care about. their XOR values won't change the inequality.
            - it also turns out that all bits i higher than MSB are forced to have the XOR values be equal, because
            all those bit values are 0. formally, for any i > MSB, we have that f_i(x,y) XOR f_i(y,z) == f_i(x,z),
            because a_{y,i} == 0.
            - so then, for a fixed y, we can just look at its MSB, and find the number of (x, z) where the
            inequality holds on f_MSB
        - how to find number of (x, z) that satisfy the inequality on a single-bit array, then? that's the last step.
            - since a_y is guaranteed to be 1, and we want the count of 1s over the interval [x, z] to be even,
            we need the parity of count_1(x, y) to be different from the parity of count_1(y, z). that's it.
        - outline:
            - iterate over y, find the MSB, then quickly find the number of pairs (x, z) such that x<=y<=z and
            f_MSB(x,y) has a different parity from f_MSB(y,z).
        - how to get there again next time?
            - iterating over the middle element is pretty much obvious
            - for a fixed middle element, use some logic to determine that only the MSB matters
            - then, realize that you need to find num of pairs (x, z) for a single bit, which just comes down to
            range sum logic and is pretty feasible by slapping on multiple layers of prefix sums
    - generalized ideas for the future:
        - when implementing something that's difficult to implement, compute everything in the easiest way possible
        (even if it requires explicitly storing something that doesn't need to be explicitly stored in an array)
        before simplifying the code. how many times do i need to tell myself this?
        - write down the exact thing that you ACTUALLY want to compute, then move on AFTERWARD to the way that you'll
        compute it. don't start with the latter, because then you might just be unclear on what you're actually trying
        to do
    */

    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    // for each bit position and prefix, counts the number of 1s.
    vector<vector<ll>> pref(30, vector<ll>(n, 0)), suf(30, vector<ll>(n, 0));
    for (int b = 0; b < 30; ++b) {
        for (int i = 0; i < n; ++i) {
            pref[b][i] = (i == 0 ? 0 : pref[b][i - 1]) + ((a[i] >> b) & 1);
        }
        for (int i = n - 1; i >= 0; --i) {
            suf[b][i] = (i == n - 1 ? 0 : suf[b][i + 1]) + ((a[i] >> b) & 1);
        }
    }

    // pref_parity[b][i][j] := number of indices k <= i such that the number of 1s that have appeared in
    // bit position b over the interval [0, k] is: even if j == 0, odd if j == 1.
    // in simpler terms. for each bit position and prefix, counts the number of indices where the prefix
    // has both an even number of 1s and an odd number of 1s.
    // it's used to efficiently calculate the number of l in [i, n - 1] such that the interval [i, l] has
    // an even or odd count of 1s. if we want [i, l] to have an odd number of 1s, we need pref[b][l] to have
    // a different parity from pref[b][i-1]. if we want [i, l] to have an even number of 1s, we need
    // pref[b][l] to have the same parity as pref[b][i-1].
    ll pref_parity[30][n][2], suf_parity[30][n][2];
    for (int b = 0; b < 30; ++b) for (int i = 0; i < n; ++i) {
        fill(pref_parity[b][i], pref_parity[b][i] + 2, 0);
        fill(suf_parity[b][i], suf_parity[b][i] + 2, 0);
    }
    for (int b = 0; b < 30; ++b) {
        for (int j = 0; j < 2; ++j) {
            for (int i = 0; i < n; ++i) {
                pref_parity[b][i][j] = (i == 0 ? 0 : pref_parity[b][i - 1][j]) + (pref[b][i] % 2 == j);
            }
            for (int i = n - 1; i >= 0; --i) {
                suf_parity[b][i][j] = (i == n - 1 ? 0 : suf_parity[b][i + 1][j]) + (suf[b][i] % 2 == j);
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        int msb = -1;
        for (int b = 29; b >= 0; --b)
            if ((a[i] >> b) & 1) {
                msb = b;
                break;
            }
        
        // parity of count of 1s strictly to left
        ll p = i == 0 ? 0 : (pref[msb][i - 1] % 2);
        // parity of count of 1s strictly to right
        ll s = (i == n - 1) ? 0 : (suf[msb][i + 1] % 2);
        // num of indices k weakly to left such that [k, i] has an even number of 1s
        ll even_left = suf_parity[msb][0][s] - (i == n - 1 ? 0 : suf_parity[msb][i + 1][s]);
        // num of indices k weakly to left such that [k, i] has an odd number of 1s
        ll odd_left = suf_parity[msb][0][s ^ 1] - (i == n - 1 ? 0 : suf_parity[msb][i + 1][s ^ 1]);
        // num of indices k weakly to right such that [i, k] has an even number of 1s
        ll even_right = pref_parity[msb][n - 1][p] - (i == 0 ? 0 : pref_parity[msb][i - 1][p]);
        // num of indices k weakly to right such that [i, k] has an odd number of 1s
        ll odd_right = pref_parity[msb][n - 1][p ^ 1] - (i == 0 ? 0 : pref_parity[msb][i - 1][p ^ 1]);
        ans += (even_left * odd_right) + (odd_left * even_right);
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
