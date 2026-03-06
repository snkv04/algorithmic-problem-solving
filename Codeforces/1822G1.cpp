#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};
const int MAXVAL = 1e6;
vector<ll> freq(MAXVAL + 1, 0);
vector<bool> processed(MAXVAL + 1, false);

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
        - given an array, find the number of ordered 3-tuples of indices whose corresponding values in the array
        form a geometric sequence
    - solution:
        - brute-force over the first element in the tuple and the ratio B, where there are 2 cases for the ratio:
            - B = 1, so all indices have the same element
            - B > 1, so all indices have different elements, but there is a bound on B that enables this brute-force
            solution to pass
    - details:
        - to obtain this bound intuitively, we can rewrite our given information as a_j = b * a_i and a_k = b^2 * a_i,
        then get
        b = sqrt(a_k / a_i) --> b <= sqrt(max(a_k / a_i)) --> b <= 1000
            - more generally, if the brute-force solution seems too slow, write out all the math, and see if we
            can place a bound on something that makes the algorithm tractable
        - optimizations:
            - to make counting frequencies more efficient, use an array instead of an ordered/unordered map
            - we don't need to process the same VALUE in the array more than once; to keep track of this, just use
            a boolean vector
            - CRITICAL optimization: if there are 1e5 tests and each of them have a single element equal to 1e6,
            then we are initializing a length-1e6 array 1e5 times; to avoid this, use a single array for all tests
                - alternatively, use a map to only store frequencies for existent values; there are downsides and
                upsides to this
            - in general, if the length of the array is smaller than the max value of the array, then iterate over
            the elements/indices themselves instead of the possible values (if possible, given the context)
                - interestingly enough, this is actually pretty important; even though the B=1 section would have
                1e6 operations while the B>1 section would have 2e8 operations, changing the B=1 section to only
                have 1e5 instead of 1e6 operations can move the solution from TLE to AC
            - we could bound B for each value of A_i, but we don't necessarily have to
    */

    // read input
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    // get max/min element and count frequencies
    int mx = 1, mn = 1e6; for (int ai : a) { mx = max(mx, ai); mn = min(mn, ai); }
    for (int ai : a) freq[ai] += 1;

    // count triples where B = 1
    // note: we iterate over the array A, and not over the values that A_i can take, because the
    // length of A is smaller than the max value across A
    ll ans = 0;
    for (int ai : a) {
        if (!processed[ai]) {
            ans += freq[ai] * (freq[ai] - 1) * (freq[ai] - 2);
            processed[ai] = true;
        }
    }

    // count triples where B > 1
    // note: we can find the max value of b for EACH a_i, but we don't have to
    for (int ai : a) processed[ai] = false;
    ll maxb = sqrt((ld) mx / mn);
    for (int ai : a) {
        if (!processed[ai]) {
            for (int b = 2; b <= maxb; ++b) {
                ll ak = (ll) ai * b * b;
                if (ak <= mx) {
                    ll aj = ai * b;
                    ans += freq[ai] * freq[aj] * freq[ak];
                }
            }

            processed[ai] = true;
        }
    }
    cout << ans << '\n';

    // update global vars for next test case
    // (the reason why we do it here is that we only want to update the elements of the array
    // that were used in this test case, to avoid filling the ENTIRE global array with 0LLs/falses
    // on every test case)
    for (int ai : a) {
        freq[ai] = 0;
        processed[ai] = false;
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
