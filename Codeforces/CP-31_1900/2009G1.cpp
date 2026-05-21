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

void remove(int x, map<int, int> &elems, map<int, int> &freqs) {
    int old_freq = elems[x];
    freqs[old_freq] -= 1;
    if (freqs[old_freq] == 0) freqs.erase(old_freq);

    elems[x] -= 1;
    if (elems[x] == 0) elems.erase(x);

    int new_freq = old_freq - 1;
    if (new_freq) freqs[new_freq] += 1;
}

void add(int x, map<int, int> &elems, map<int, int> &freqs) {
    int old_freq = elems.count(x) ? elems[x] : 0;
    if (old_freq) {
        freqs[old_freq] -= 1;
        if (freqs[old_freq] == 0) freqs.erase(old_freq);
    }

    elems[x] += 1;

    int new_freq = old_freq + 1;
    freqs[new_freq] += 1;
}

void solve() {
    /*
    - few useful ideas here:
        - if we want elements that are consecutive and increasing, then note that if we plot their index as
        x and their value as y, then those elements will fall on the same shift of y=x. if we subtract all
        the elements by their index, then all of them will be the same, because the value increases at the
        same rate as the index.
            - more generally, if we want to group elements together that have different values but share some
            same property, then it could be useful to see if we can literally map them to the same value, because
            elements having the same value has some nice properties (like being part of the same entry in a map)
        - can precompute the answers to all queries before any queries are asked
        - can store a multiset of elements as well as a multiset of those elements' frequencies, almost like
        a data structure that is a derivative of another data structure. they both hold properties of the same
        underlying information (where the "same underlying information" is the set of array values in the current
        sliding window), but they hold different properties of that information, and the second one is based on
        the first. this pattern appears a lot, even in production.
    */

    // gets array and shifts it down by index
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(n);
    cin >> a;
    for (int i = 0; i < n; ++i) a[i] -= i;

    // gets initial maps
    map<int, int> elems, freqs;
    for (int i = 0; i < k; ++i) {
        elems[a[i]] += 1;
    }
    for (auto [k, v] : elems) freqs[v] += 1;

    // updates map for each possible window and stores answer for that window
    vector<int> ans(n, 1e9);
    ans[k - 1] = k - freqs.rbegin()->first;
    for (int i = k; i < n; ++i) {
        int adding = a[i], removing = a[i - k];
        remove(removing, elems, freqs);
        add(adding, elems, freqs);
        ans[i] = k - freqs.rbegin()->first;
    }

    // answers queries in O(1)
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        cout << ans[r] << '\n';
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
