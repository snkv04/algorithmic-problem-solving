#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7; // 998244353;
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

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
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

ll slow_pow(ll b, ll e) {
    ll result = 1;
    while (e--) result *= b;
    return result;
}

int l(int digit, vector<int> &d) {
    int result = -1;
    for (int candidate : d) {
        if (candidate < digit) result = candidate;
    }
    return result;
}

int g(int digit, vector<int> &d) {
    for (int candidate : d) {
        if (candidate > digit) return candidate;
    }
    return -1;
}

void solve() {
    // reads in input
    ll a;
    int n;
    cin >> a >> n;
    vector<int> d(n);
    cin >> d;
    if (a == 0) {
        cout << d[0] << endl;
        return;
    }
    if (n == 1 && d[0] == 0) {
        cout << a << endl;
        return;
    }

    // gets digits and says which most-significant prefixes of digits we have
    vector<int> digits;
    ll copy = a;
    while (copy) {
        digits.push_back(copy % 10);
        copy /= 10;
    }
    vector<bool> has(digits.size(), false);
    for (int i = has.size() - 1; i >= 0; --i) {
        if (std::find(d.begin(), d.end(), digits[i]) == d.end()) {
            break;
        } else {
            has[i] = true;
        }
    }
    if (has[0]) {
        cout << 0 << endl;
        return;
    }

    // tries basic candidates
    ll ans = 9e18;
    ll candidate = 0;
    if (digits.size() > 1) {
        // edge case: if a is only 1 digit, can't (necessarily) set that digit to 0 and
        // everything to left to max, because there might not be anything to left
        for (int i = 0; i < digits.size() - 1; ++i) candidate += d[n - 1] * slow_pow(10, i);
        ans = min(ans, abs(a - candidate));
    }
    candidate = 0;
    for (int i = 0; i < digits.size(); ++i) candidate += d[0] * slow_pow(10, i);
    candidate += (d[0] == 0 ? d[1] : d[0]) * slow_pow(10, digits.size());
    ans = min(ans, abs(a - candidate));

    // preprocessing for brute-forcing candidates
    vector<ll> maxpref(digits.size(), 0), minpref(digits.size(), 0);
    for (int i = 0; i < digits.size(); ++i) {
        maxpref[i] = (i == 0 ? 0 : maxpref[i - 1]) + d[n - 1] * slow_pow(10, i);
        minpref[i] = (i == 0 ? 0 : minpref[i - 1]) + d[0] * slow_pow(10, i);
    }

    // brute-forces candidates
    ll same = 0;
    for (int i = digits.size() - 1; i >= -1; --i) {
        // have this digit be the first that's greater.
        // everything larger is same, everything smaller is minimum
        if (g(digits[i], d) != -1) {
            ll candidate = same + (i == 0 ? 0 : minpref[i - 1]) + g(digits[i], d) * slow_pow(10, i);
            ans = min(ans, abs(a - candidate));
        }

        // have this digit be the first that's less.
        // everything larger is same, everything smaller is maximum
        if (l(digits[i], d) != -1) {
            ll candidate = same + (i == 0 ? 0 : maxpref[i - 1]) + l(digits[i], d) * slow_pow(10, i);
            ans = min(ans, abs(a - candidate));
        }

        // updates the "same" value, which is just everything that's more significant than the next "current digit"
        if (!has[i]) break;
        else same += digits[i] * slow_pow(10, i);
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve();
    }

    return 0;
}
