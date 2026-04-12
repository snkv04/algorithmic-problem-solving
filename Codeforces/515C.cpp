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

vector<int> process(int digit) {
    vector<int> res;
    if (digit == 4) {
        res.push_back(3);
        res.push_back(2);
        res.push_back(2);
    } else if (digit == 6) {
        res.push_back(5);
        res.push_back(3);
    } else if (digit == 8) {
        res.push_back(7);
        for (int i = 0; i < 3; ++i) res.push_back(2);
    } else if (digit == 9) {
        res.push_back(7);
        res.push_back(3);
        res.push_back(3);
        res.push_back(2);
    } else {
        res.push_back(digit);
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<int> digits;
    for (int i = 0; i < n; ++i) if (s[i] - '0' >= 2) digits.push_back(s[i] - '0');

    vector<int> new_digits;
    for (auto d : digits) {
        auto converted = process(d);
        for (int d2 : converted) new_digits.push_back(d2);
    }
    sort(new_digits.begin(), new_digits.end());
    reverse(new_digits.begin(), new_digits.end());

    for (int d : new_digits) cout << d;
    cout << endl;
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
