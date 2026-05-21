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
    - core idea is normalization. there is a lot of nuance hidden here.
        - yes, it is true that even though normalizing the segments does not change the initial value, it
        CAN tangibly change the result of performing a single operation on an index pair (i, j). namely,
        the value obtained by {performing an operation} and {normalizing then performing an operation}
        is different.
        - however, it is also true that the maximum target value obtainable is the same whether we perform
        normalization or not.
            - to arrive at this conclusion, enumerate all possible segment cases. then, observe that even
            though normalizing a segment (swapping a_i and b_i if a_i > b_i) CAN increase the value of
            performing a (b_i, b_j) swap between indices i and j compared to not normalizing it, the
            resulting value is either:
                - equal to what we would've gotten without normalization
                - equal to what we would've gotten without performing a swap operation on those 2 segments at all
            so it actually doesn't matter. it just simplifies things without changing the answer.
            - why does it simplify things? basically, it just adds some structure: for all i, a_i <= b_i.
    */

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    cin >> a >> b;

    for (int i = 0; i < n; ++i) {
        if (a[i] > b[i]) swap(a[i], b[i]);
    }

    int mxa = -2e9, mnb = 2e9;
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        mxa = max(mxa, a[i]);
        mnb = min(mnb, b[i]);
        sum += abs(b[i] - a[i]);
    }
    sum += max(0, 2 * (mxa - mnb));
    cout << sum << endl;
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
