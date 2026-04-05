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

int main() {
    /*
    - problem:
        - we have an nx2 tower. we can use shapes of size (any integer)x(any integer) to fill it.
        - how many ways can we fill the tower?
    - solution:
        - there are 6 ways that the top row of the tower can be configured:
               _ _
            - | | |
               _
            - | | |
                 _
            - | | |

            - | | |
               _ _
            - |   |

            - |   |

        - so, we can keep track of the number of ways for each configuration at each row based
        on the previous row, and add up the 1st and 5th way for the final answer
    - details:
        - why do we only keep track of the top row's information?
            - the alternative would be to keep track of the number of ways for the top row to be
            connected + closed and disconnected + closed (case 5 and case 1). that would require
            knowing the heights of the pieces and possibly some combinatorics, and it would still
            be correct, but it's a lot slower.
            - it basically turns out that this information (the 6 cases) is simply enough. it covers
            all possible cases. if a square has an open top, then it doesn't have to have started on
            that row; it could have started much below, and the open tops just happened consecutively
            in that column. similarly, we can have two closed tops in a row. in other words, the
            "open"/"close" information only is useful to say if the next row can connect to it,
            and it doesn't say when the block actually began.
        - implementation detail: it turns out that all of the first 4 cases and the last 2 cases each
        share the same number of combinations, so for ease of implementation, we only keep track of
        "number of ways for a single configuration where both columns are disconnected" and
        "number of ways for a single configuration where both columns are connected", and then use
        those instead.
        - if it was the case that each block had a limited height, then we couldn't just keep track of
        if the block was open (could connect to next row) or closed (couldn't connect to next row).
        instead, we'd also have to keep track of the length of the block. however, that is not the
        case in this problem.
    */

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    constexpr int MAXN = 1e6;
    vector<vector<ll>> mem(MAXN + 1, vector<ll>(2, 0));
    mem[1][0] = mem[1][1] = 1;
    for (int i = 2; i <= MAXN; ++i) {
        mem[i][0] = (4 * mem[i - 1][0] + mem[i - 1][1]) % MOD;
        mem[i][1] = (2 * mem[i - 1][1] + mem[i - 1][0]) % MOD;
    }

    int t = 1;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        ll ans = (mem[n][0] + mem[n][1]) % MOD;
        cout << ans << endl;
    }

    return 0;
}
