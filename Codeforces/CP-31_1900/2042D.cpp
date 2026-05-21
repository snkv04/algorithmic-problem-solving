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
        - we are given a bunch of segments
        - for each segment s, look at all the segments that fully cover it. across all of those,
        take the leftmost right end and find the distance from that to s.right, and take the rightmost
        left end and find the distance from that to s.left.
    - solution:
        - the key idea is to just separate it into two individual problems. instead of:
            - finding all the covering segments for each segment, then finding the leftmost right end and
            rightmost left end across those
        we can separately:
            - find the leftmost right-end of all the covering segments
            - find the rightmost left-end of all the covering segments
        which makes it a lot easier.
        - to do so, sort all segments by their left bound. then, when iterating over them, all segments
        that cover the current one will have already been processed, so we look at the minimum right end
        that is >= the current segment's right end.
    - useful ideas:
        - see if we can factor out the problem into easy tasks.
        - similar to how we can separately handle large and small inputs in different ways, we can separately
        handle distinct and non-distinct items in different ways.
            - we should be careful though. we can't exclude all distinct elements from the sorted segments,
            setting their answers to be 0, and then answer the other segments. those distinct elements might
            be the "covering segment" for other segments.
            - so, instead of setting all their answers to be 0 at the beginning and excluding them,
            we include them and then set all their answers to be 0 at the end.
    */

    int n;
    cin >> n;
    map<pair<int, int>, vector<int>> segments;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        segments[make_pair(l, r)].push_back(i);
    }

    vector<array<int, 3>> by_left, by_right;
    vector<int> ans(n, 0);
    for (auto [k, v] : segments) {
        array<int, 3> segment = {v[0], k.first, k.second};
        by_left.push_back(segment);
        by_right.push_back(segment);
    }
    sort(by_left.begin(), by_left.end(), [](const array<int, 3> &a, const array<int, 3> &b) {
        if (a[1] != b[1]) {
            return a[1] < b[1];
        } else {
            return a[2] > b[2];
        }
    });
    sort(by_right.begin(), by_right.end(), [](const array<int, 3> &a, const array<int, 3> &b) {
        if (a[2] != b[2]) {
            return a[2] > b[2];
        } else {
            return a[1] < b[1];
        }
    });

    set<int> rights, lefts;
    for (auto [idx, l, r] : by_left) {
        if (rights.lower_bound(r) != rights.end()) {
            ans[idx] += *rights.lower_bound(r) - r;
        }
        rights.insert(r);
    }
    for (auto [idx, l, r] : by_right) {
        auto it = lefts.upper_bound(l);
        if (it != lefts.begin()) {
            --it;
            ans[idx] += l - *it;
        }
        lefts.insert(l);
    }

    for (auto [k, v] : segments) {
        if (v.size() > 1) {
            for (auto idx : v) {
                ans[idx] = 0;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << '\n';
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
