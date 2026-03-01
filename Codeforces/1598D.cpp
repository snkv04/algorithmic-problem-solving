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
        - given two arrays A and B, find the number of triples of indices (where order doesn't matter) where
        either the A values at those indices are all different, the B values at those indices are all different,
        or both conditions are met
    - solution:
        - find the total number of triples, then subtract the number of triples where NEITHER condition is met;
        due to the condition that all problems are different, the second part can be computed efficiently in O(n)
    - details:
        - instead of there being two arrays that are indexed by i, let's think about each index i having two
        properties: i_a = a[i] and i_b = b[i]
        - for NEITHER condition to be met, this means that "the A values aren't all different AND the B values aren't
        all different"; this can be broken down into "(across the triple, there's 2 different A values OR only 1 total
        A value) AND (across the triple, there's 2 different B values OR only 1 total B value)". let's look at each 
        of the 2x2=4 cases:
            - (1) there's only 1 A value and only 1 B value. namely, the triple looks like ((p, r), (p, r), (p, r));
            this is impossible
            - (2) there's only 1 A value and 2 B values. namely, the triple looks like ((p, r), (p, r), (p, s));
            this is impossible
            - (3) there's 2 A values and only 1 B value. namely, the triple looks like ((p, r), (p, r), (q, r));
            this is impossible
            - (4) there's 2 A values and 2 B values. namely, either:
                - we have ((p, r), (p, r), (q, s)); this is impossible
                - we have ((p, r), (p, s), (q, r)); this is FINE! now we count (i1, i2, i3) satisfying this.
            - in simple terms, a triple (i1, i2, i3) where all 3 i's share an A value and at least 2 i's share a B value
            is impossible; same thing if we flip A and B. so, the "neither condition from the problem is met" case can
            be reduced into: triples where exactly 2 indices share an A and exactly 2 indices share a B
        - so basically, that 4th case where NEITHER condition from the problem is met seems to have 4 sub-cases, but 3
        of them are impossible. we now just have to count the number of triples with the form ((p, r), (p, s), (q, r)).
        this can be done by brute-forcing all possible values of (p, r) (which can be done by just iterating i from 1 to n,
        and setting p=a[i] and r=b[i]), and multiplying the possibilities for (p, s) and (q, r) together.
            - why is it so straightforward? if we know (p, r), or the "central" index, then that defines the form that the
            (a, b) values of the other two indices must follow.
    */

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
    }

    map<int, int> cnta, cntb;
    for (int i = 0; i < n; ++i) {
        cnta[a[i]] += 1;
        cntb[b[i]] += 1;
    }

    ll ans = 1LL * n * (n-1) * (n-2) / 6;
    for (int i = 0; i < n; ++i) {
        ans -= 1LL * (cnta[a[i]] - 1) * (cntb[b[i]] - 1);
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
