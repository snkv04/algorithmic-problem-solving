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

int query(int l, int r, vector<int> &true_indices) {
    cout << "? " << r - l + 1 << " ";
    for (int i = l; i <= r; ++i) {
        cout << true_indices[i] << " ";
    }
    cout << endl;
    int result;
    cin >> result;
    return result;
}

void solve() {
    /*
    - summary:
        - we can binary search to find the leftmost index whose corresponding prefix contains all 3 instances
        of the triple-instance element. that index holds one such instance. then, we remove that index from the
        array, hold onto it to always include it in our future queries, and proceed to binary search again on
        the array that excludes that index.
    - implementation notes:
        - in the problem, there's an array. each index in [1, 2n+1] holds an element. we can make our own array
        that holds those indices in a slightly shuffled order. why? it's really just an implementation detail.
        the real, important logic is already written above in the summary. all that this new array does is allow
        us to binary search on the elements outside of the ones we've already found, while including those that
        we've found in the prefix we query for.
        - this is only really possible since we query a subset of the given array, not a subarray. if we couldn't
        do that, then the logic of "tell me about this set of contiguous elements PLUS a couple other arbitrary
        elements i'm holding on to" wouldn't constitute a valid query.
    */

    int n;
    cin >> n;
    vector<int> true_indices;
    for (int i = 1; i <= 2 * n + 1; ++i) true_indices.push_back(i);  // indices of elements from problem

    vector<int> ans;
    for (int _ = 0; _ < 3; ++_) {
        // finds leftmost index holding all 3 instances
        int lo = 0, hi = 2 * n, idx_in_arr = -1;  // index in our true_indices array
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            int result = query(0, mid, true_indices);
            if (result % 2 != (mid + 1) % 2) {
                idx_in_arr = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        // saves that index to be included in all future queries
        ans.push_back(true_indices[idx_in_arr]);
        std::rotate(true_indices.begin(), true_indices.begin() + idx_in_arr, true_indices.begin() + idx_in_arr + 1);
    }

    cout << "! ";
    for (auto true_idx : ans) cout << true_idx << " ";
    cout << endl;
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
