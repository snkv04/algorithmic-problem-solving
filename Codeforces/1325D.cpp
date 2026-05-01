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
        - make a minimum-length array with bitwise XOR equal to U and sum equal to V
    - solution:
        - first, handle base cases
            - they're not immediately trivial to find!
        - then, instead of going bit-by-bit and trying to build an array that matches both u and v,
        first make the first element equal to u, and then go bit-by-bit and build an array that
        matches delta = v - u
            - why?
                - first, recognize that for each bit b that is activated in u, our final array needs
                an odd number of instances of that bit
                - so, we might as well put a single instance in the first element of our array; as a
                result, the remaining things we do to the array just need to maintain the parity of
                the number of instances of every bit
        - to match delta, just go bit-by-bit and for each activated bit, add 2 instances of the next-lower
        bit; if the next-lower bit is already there in the first element (for any bit), then we need
        3 elements total, while if it's not there in the first element (for all bits), then we only
        need 2 elements total
            - this maintains the XOR being equal to u, because for every bit, we only add an even
            number (2) of instances of that bit
            - think of it as the 3-element case, but as said in the editorial, we're basically just
            merging the first 2 elements because they don't overlap in any bits (i.e., their bitwise
            XOR is 0)
    */

    ll u, v;
    cin >> u >> v;
    if (u % 2 != v % 2 || v < u) {
        cout << "-1\n";
        return;
    }
    if (u == 0 && v == 0) {
        cout << "0\n";
        return;
    }

    vector<int> cnt(61, 0);
    for (ll i = 0; i <= 60; ++i) {
        if ((u >> i) & 1) {
            cnt[i] += 1;
        }
    }
    v -= u;

    for (int i = 0; i <= 60; ++i) {
        if ((v >> i) & 1) {
            cnt[i - 1] += 2;
        }
    }

    int ans = 0;
    for (int i = 0; i <= 60; ++i) ans = max(ans, cnt[i]);
    vector<ll> arr(ans, 0);
    for (int i = 0; i <= 60; ++i) {
        for (int j = 0; j < cnt[i]; ++j) {
            arr[j] += 1LL << i;
        }
    }
    cout << ans << "\n";
    for (ll num : arr) cout << num << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
