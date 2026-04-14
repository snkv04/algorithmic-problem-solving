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

int query(int left, int right, map<pair<int, int>, int> &cache) {
    if (left == right) {
        return 1;
    }

    auto p = make_pair(left, right);
    int d;
    if (cache.count(p)) {
        d = cache[p];
    } else {
        int k = right - left + 1;
        cout << "? " << k << " ";
        for (int i = left; i <= right; ++i) {
            cout << i << " ";
        }
        cout << endl;
        cin >> d;
        cache[p] = d;
    }
    return d;
}

void solve() {
    /*
    - summary of solution:
        - binary search to find leftmost prefix that contains all 3 instances
        - binary search to find rightmost suffix that contains all 3 instances
        - once we have those 2 bounds, we can find the 3rd (middle) instance by binary searching on prefixes of
        that (l, r) window, and for each, removing the l'th element and including it; if the distinct element count
        increases, then we still are holding that middle element
    - notes:
        - my observation was that if we query an odd number of elements and we have an even number of distinct elements,
        then it must include all 3 instances of the triple-appearance element. however, this can be made more general:
        if we query k elements and the result's parity isn't k, then it includes all 3 elements. why? what's the
        underlying principle? if the parity doesn't match, then the total number of instances of non-distinct (repeated)
        elements is odd, meaning that it must contain all 3 instances. to reach this general form, break the situation
        down to be as simple as possible (the k objects contains distinct elements, and non-distinct elements) then
        think about that simple situation deeply.
    */

    int n;
    cin >> n;

    map<pair<int, int>, int> cache;
    int lo = 1, hi = n, loose_r = -1;
    while (lo <= hi) {
        int m = (lo + hi) / 2;

        int left = 1;
        int right = 2 * m + 1;
        int d = query(left, right, cache);
        if (d % 2 == 0) {
            loose_r = right;
            hi = m - 1;
        } else {
            lo = m + 1;
        }
    }
    lo = 0;
    hi = (loose_r - 1) / 2 - 1;
    int loose_l = -1;
    while (lo <= hi) {
        int m = (lo + hi) / 2;

        int left = 2 * m + 1;
        int right = loose_r;
        int d = query(left, right, cache);
        if (d % 2 == 0) {
            loose_l = 2 * m + 1;
            lo = m + 1;
        } else {
            hi = m - 1;
        }
    }
    // cout << "loose l = " << loose_l << ", loose r = " << loose_r << endl;

    int tight_l = loose_l, tight_r = loose_r;
    // cout << "checking right" << endl;
    if (query(loose_l, loose_r, cache) != query(loose_l, loose_r - 1, cache)) {
        tight_r -= 1;
    }
    // cout << "checking left" << endl;
    if (query(loose_l, loose_r, cache) != query(loose_l + 1, loose_r, cache)) {
        tight_l += 1;
    }
    assert(tight_r - tight_l >= 2);
    // cout << "tight l = " << tight_l << ", tight r = " << tight_r << endl;

    lo = tight_l + 1; hi = tight_r - 1; int idx = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        // cout << "querying with: (" << tight_l << ", " << mid << ")\n";
        int with = query(tight_l, mid, cache);
        // cout << "querying without: (" << tight_l + 1 << ", " << mid << ")\n";
        int without = query(tight_l + 1, mid, cache);
        if (without == with + 1) {
            idx = mid;
            hi = mid - 1;
        } else {
            assert(without == with - 1);
            lo = mid + 1;
        }
    }

    cout << "! " << tight_l << " " << idx << " " << tight_r << endl;
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
