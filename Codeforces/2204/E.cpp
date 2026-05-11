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

vector<int> get_digits(int num) {
    vector<int> result;
    while (num) {
        result.push_back(num % 10);
        num /= 10;
    }
    return result;
}

int get_sum(int num) {
    vector<int> digits = get_digits(num);
    return std::accumulate(digits.begin(), digits.end(), 0);
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    if (n == 1) {
        cout << s << "\n";
        return;
    }

    // builds frequency map (stored in a dynamic list)
    vector<int> freq(10, 0);
    int digit_sum = 0;
    for (int i = 0; i < n; ++i) {
        int digit = s[i] - '0';
        freq[digit] += 1;
        digit_sum += digit;
    }

    // "first number digit sum"
    for (int fnds = 1; fnds <= digit_sum; ++fnds) {
        // deterministically gets rest of digits
        vector<int> remaining = {fnds};
        while (remaining.back() >= 10) {
            remaining.push_back(get_sum(remaining.back()));
        }

        // makes sure rest of digits have enough frequency bandwidth (they all fit into the
        // frequency map without issues)
        vector<int> freq_copy = freq;
        bool valid = true;
        for (int num : remaining) {
            auto digits = get_digits(num);
            for (int d : digits) {
                if (!freq_copy[d]) {
                    valid = false;
                    break;
                }
                freq_copy[d] -= 1;
            }
        }
        if (!valid) continue;

        // builds first element, and checks its sum
        int sum = 0;
        for (int i = 0; i < 10; ++i) sum += i * freq_copy[i];
        if (sum != fnds) continue;

        // all checks passed -> build final string
        stringstream ss;
        for (int i = 9; i >= 0; --i) {
            while (freq_copy[i]--) {
                ss << i;
            }
        }
        for (int num : remaining) ss << num;
        cout << ss.str() << "\n";
        return;
    }
    throw std::logic_error("A valid sequence must exist");
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
