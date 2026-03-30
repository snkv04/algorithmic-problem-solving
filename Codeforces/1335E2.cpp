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
        - find the longest subsequence of the given array such that it can be broken into 3 segments, where
        the first and third segments have the same length and are filled with the same character, and the
        second segment is also filled only with 1 character
    - solution:
        - we can iterate over the character used in the outside block, and for each, iterate on the length
        of the first and third block; if we know that length L, then we can greedily take the first L and
        last L occurrences of that character
        - then, we look over all characters to find the most frequent one between those 2 blocks, and use
        that as the middle
    - details:
        - since there are only O(n) possible places for the first block to end, this solution is O(n * max(a_i))
        - when the array is sufficiently close to the memory limit, using an array of long longs instead of
        ints can actually cause the memory limit to be exceeded
    */

    // reads in the input
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    // computes prefix sums of counts for each character (in order to find the most frequent character
    // in a given window) and the index of each character's k'th occurrence (in order to find where the
    // last element of the first block and first element of the last block are located)
    constexpr int MAX_AI = 200;
    vector<vector<int>> cnt_pref(MAX_AI + 1, vector<int>(n, 0));
    vector<vector<int>> cnt_to_idx(MAX_AI + 1, vector<int>(1, -1));
    for (int i = 0; i < n; ++i) {
        int ai = a[i];
        cnt_to_idx[ai].push_back(i);
        if (i) for (int aj = 1; aj <= MAX_AI; ++aj) cnt_pref[aj][i] = cnt_pref[aj][i-1];
        cnt_pref[ai][i] += 1;
    }

    // iterates through each character that could be the end of the first block, and for each, finds
    // the location of the third block then finds the most frequent character that could compose the
    // second block
    int ans = 1;
    for (int i = 0; i < n; ++i) {
        int ai = a[i];
        int cnt = cnt_pref[ai][i];
        int total = cnt_to_idx[ai].size() - 1;
        if (cnt > total / 2) continue;

        int l = i + 1;
        int r = cnt_to_idx[ai][total + 1 - cnt] - 1;
        for (int middle = 1; middle <= MAX_AI; ++middle) {
            int cnt_middle = cnt_pref[middle][r] - cnt_pref[middle][l-1];
            ans = max(ans, 2 * cnt + cnt_middle);
        }
    }
    cout << ans << '\n';
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
