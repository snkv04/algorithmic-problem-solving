#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return _query(2 * v, l, m, ql, qr)
            + _query(2 * v + 1, m + 1, r, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }
};

void solve() {
    /*
    what's the most brute-force-like possible way to think about this? first of all, there are
    2^n possible subsets of problems that we can choose to attempt (let's call any such subset A).
    for each A, there are 2^len(A) ways to assign correct/incorrect labels to the problems that
    we choose. we can reduce that to a probability distribution by setting the random variable X,
    for a given subset of problems attempted A, to be the number of points received after attempting
    those problems (if A is fixed, then X has a bijection with the number of correct answers). some
    of those point values are >= k. if you sum up the probabilities across all point values, the sum
    is 1, so the probability that the number of points is >= k can be found easily. this is a single
    number for each subset A. so, the problem reduces to, across all subsets (since the thing that we
    are able to choose is which problems we attempt), find the maximum possible probability that we
    get >= k points.

    first observation: for a given number len(A) of problems attempted, there's only one (or possibly
    multiple, but they'd all be identical since the probabilities for the questions are the same)
    subset of problems that we'd want to attempt, and that is the subset of len(A) problems with the
    highest probabilities of correctness. this EXPONENTIALLY cuts down the subsets that we are looking
    across (in typical DP fashion :) ) from 2^N to N. we just have to make sure to sort, and that sorting
    imposes a restriction that reduces all classes of subsets (where a class is defined by its size) to
    a single subset.

    now, we just look across all possible values of numbers of problems that we want to attempt, and for
    each, we find the probability that the number of points we get is >= k. to do that second part, we
    can use DP, where dp[i][j] is the probability that after answering exactly k questions (and leaving
    the other n-k ones blank), where the k questions we're answering are the ones with highest probability,
    we end up with exactly j points. for computing the probability that we get >= k points for a given i,
    we just sum up the probabilities in the dp[i] row where j >= k.

    KEEP IN MIND that the values of j can actually be negative, up to (or down to?) -n, because of the
    way that the point system works here. for dealing with this, we can either hold the DP table in a
    map, or shift the indices (in a way that kind of hashes each state (i, j)) to all fit into a table
    that has non-negative indices (as is standard).

    generalizable ideas?
    - if we want to consider all possible subsets, then think of if there is a way to reduce the subsets
    we're looking across by seeing if there are some subsets that we simply would not want. in this
    case, for any given subset size, we only care about a single such subset, which is the one with the
    highest probabilities across the board
    - in a DP table, some of the dimensions might actually require negative values, which could require
    representing each state with some sort of mapping function (such as shifting from [-n, n] to [0, 2n])
    if i don't just use a map
    - it seems like recursion is slower than iteration, but i don't know if that's because of the call
    stack or because we're passing references to the DP table (tried both DP table and DP hashmap, which
    hashed the pair (i, j), and it seems like the DP table is slower, so the issue might just be the size
    of the thing that we are passing a reference to, though that doesn't seem to make sense since the
    reference itself should be pretty small)
    */

    int n, k;
    cin >> n >> k;
    vector<double> p(n); for (int i = 0; i < n; ++i) cin >> p[i];
    sort(p.begin(), p.end());
    reverse(p.begin(), p.end());

    vector<vector<double>> dp(n+1, vector<double>(2*n+1, 0));
    dp[0][n] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= 2*n; ++j) {
            if (j) dp[i][j] += p[i-1] * dp[i-1][j-1];
            if (j < 2 * n) dp[i][j] += (1 - p[i-1]) * dp[i-1][j+1];
        }
    }
    // cout << "dp = \n";
    // for (int i = 0; i <= n; ++i) {
    //     for (int j = 0; j <= 2 * n; ++j) {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    double best = 0;
    for (int i = 1; i <= n; ++i) {
        double curr = 0;
        for (int j = n+k; j <= 2 * n; ++j) {
            curr += dp[i][j];
        }
        best = max(best, curr);
    }
    cout << best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
