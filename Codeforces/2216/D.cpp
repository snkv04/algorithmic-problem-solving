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

void solve(const vector<int> &d) {
    ll n;
    cin >> n;

    ll ans = 0;
    for (ll b = 2; 1 + b + b * b <= n; ++b) {
        int len = 0;
        ll copy = n;
        ll g = 0;
        while (true) {
            int digit = copy % b;
            ++len;
            if (copy / b == 0) {
                g = gcd(g, len);
                break;
            } else {
                copy /= b;
                if (copy % b != digit) {
                    g = gcd(g, len);
                    len = 0;
                }
            }
        }
        if (g >= 2) {
            ans += d[g];
        }
    }

    ll rt = sqrt(n);
    for (ll digit = 1; digit <= rt; ++digit) {
        if (n % digit == 0) {
            ll b = n / digit - 1;
            if (b > digit && b >= 2) {
                ++ans;
            }
        }
    }

    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> d(41, 0);
    for (int i = 2; i <= 40; ++i) {
        for (int j = i; j <= 40; j += i) {
            d[j] += 1;
        }
    }

    int t = 1;
    cin >> t;
    while (t--) {
        solve(d);
    }

    return 0;
}
