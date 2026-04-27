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
    - interesting ideas:
        - if we have an infinite number of 2s and 3s, then any sum can be made
            - if we only have 2s, then we can't make any odd numbers
            - if we only have 3s, then there are some even numbers we can't make
            - of course, if we have 1s, then we can make anything, but in this problem, we can't have
            a segment of length 1
            - more generally, we look at the segment lengths we are allowed to make (>= 2), and find
            the smallest subset of that set which can generate the whole set through composing them together,
            which is {2, 3} in this problem
        - always try to make operations as primitive as possible, so you have fewer choices of operations
        to search through
    */

    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    ll ans = 1e18;
    for (int t = 0; t < 3; ++t) {
        vector<ll> mem(n + 1, 0);
        mem[1] = 1e18;
        for (int i = 2; i <= n; ++i) {
            ll if2 = abs(a[i - 1] - a[i - 2]);
            mem[i] = if2 + mem[i - 2];

            if (i >= 3) {
                array<int, 3> arr = {a[i - 1], a[i - 2], a[i - 3]};
                sort(arr.begin(), arr.end());
                ll if3 = (arr[1] - arr[0]) + (arr[2] - arr[1]);
                mem[i] = min(mem[i], if3 + mem[i - 3]);
            }
        }
        ans = min(ans, mem[n]);

        a.push_back(a[0]);
        a.erase(a.begin());
    }
    cout << ans << endl;
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
