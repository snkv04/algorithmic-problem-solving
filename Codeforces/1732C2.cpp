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
        - for each query defined by (L, R),
        across all subsegments (l, r) such that L <= l <= r <= R, find the maximum value of
        sum(a[l], a[l+1], ..., a[r]) - xor(a[l], a[l+1], ..., a[r])
        - if there are multiple, then give any such subarray with the shortest length
    - solution:
        - same brute-force solution as the easy version: instead of searching over ALL possible (l, r)
        where L <= l <= r <= R, we can cut down our search space by iterating through all possible l and
        efficiently finding the closest r using binary search
        - however, we can actually cut down our search space even more:
            - notice that some values of l are so far to the right that even f(l, R) won't give f(L, R)
            - we can find that the number of elements we'll have to look over until we hit that value of
            l, where l starts to become useless, is actually bounded (over the non-zero elements); by the
            pigeonhole principle, after 31 non-zero elements, at least 1 bit will have had to appear twice
            (and therefore get flipped off), meaning that somewhere in those 31 elements, f(l, R) is strictly
            less than f(l - 1, R)
            - in other words, the number of elements on the left end of that query segment [L, R] such that
            f(l, R) == f(l + 1, R) due to the sum increment being equal to the XOR increment (formally,
            sum(l, R) - sum(l+1, R) == xor(l, R) - xor(l+1, R)) is bounded, assuming we are looking at nonzero
            elements
            - quick note: we do, however, need to skip the elements equal to 0, because those won't change
            either the sum or XOR and the number of those is unbounded; however, we can preprocess these away
        - so, for each query, we only look at 31 values of l, and find r for each; therefore, our time
        complexity is O(n + q * (31 log n))
    - generalized ideas for the future:
        - like Yann LeCun said, most problems are search problems, so always think about if the
        search space can be cut down by eliminating unlikely or impossible solutions!
        - in order to go from "iterate through all possible l values" to "only iterate through around 31
        possible l values", we need to find a reason for why we can bound the size of our search space, but
        in this problem, we only can bound the search space over the nonzero elements; more generally, if our
        search space consists of some values, then in order to find a bound, we may have to find some subset
        of the space that we completely skip and then only bound the other subset
    */

    // reads in input
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    cin >> a;

    // precomputes prefix sums and prefix XOR sums
    vector<ll> pref_sum(n), pref_xor(n);
    for (int i = 0; i < n; ++i) {
        pref_sum[i] = (i == 0 ? 0 : pref_sum[i - 1]) + a[i];
        pref_xor[i] = (i == 0 ? 0 : pref_xor[i - 1]) ^ a[i];
    }

    // finds indices of nonzero elements
    vector<int> nonzero_indices;
    for (int i = 0; i < n; ++i) if (a[i]) nonzero_indices.push_back(i);

    // processes queries
    auto get_val = [&](int l, int r) {
        return (pref_sum[r] - (l == 0 ? 0 : pref_sum[l - 1])) -
               (pref_xor[r] ^ (l == 0 ? 0 : pref_xor[l - 1]));
    };
    while (q--) {
        // reads in left and right bound of query
        int l, r;
        cin >> l >> r;
        --l; --r;

        // finds farthest-away left and right indices across nonzero elements
        // within the [L_i, R_i] subarray. basically, takes the given [L, R]
        // and finds it within the nonzero elements
        int lo = 0, hi = nonzero_indices.size() - 1, l_idx = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (nonzero_indices[mid] >= l) {
                l_idx = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        lo = 0; hi = nonzero_indices.size() - 1; int r_idx = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (nonzero_indices[mid] <= r) {
                r_idx = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        if (l_idx == -1 || r_idx == -1 || l_idx > r_idx) {
            // the entire subarray just consists of zeros
            cout << l + 1 << ' ' << l + 1 << '\n';
            continue;
        }
        
        // iterates only over 31 values of l within [L, R], where a[l] != 0
        ll ans = get_val(l, r);
        int ans_l = l, ans_r = r;
        for (int idx = l_idx; idx <= min(r_idx, l_idx + 30); ++idx) {
            // finds the corresponding r to the l
            int curr_l = nonzero_indices[idx];
            int lo = idx, hi = r_idx, curr_r = -1;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (get_val(curr_l, nonzero_indices[mid]) == ans) {
                    curr_r = nonzero_indices[mid];
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }

            // checks if it's the best subarray
            if (curr_r != -1 && curr_r - curr_l < ans_r - ans_l) {
                ans_l = curr_l;
                ans_r = curr_r;
            }
        }
        cout << ans_l + 1 << ' ' << ans_r + 1 << '\n';
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
