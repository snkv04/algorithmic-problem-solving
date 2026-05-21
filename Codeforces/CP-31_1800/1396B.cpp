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
    - ideas:
        - if there's a dominating pile, of course the first player will win
        - otherwise, it's basically the pairing game, and odd means first will win while even means second
        will win.
            - why is it basically the pairing game? basically, why are we always able to win if odd and we
            always lose if even?
            if odd, we can always take a stone from the max pile, and we can show that the other person's move
            never makes us unable to access the max pile. gradually, we flatten down the array into all 1s,
            and there's an odd number, so we clearly win.
            if even, we can take a stone from any pile (including the max pile), and the other player will
            always be able to take a stone from the new max pile, in all cases, and they'll win by the above
            logic.
        - basically, we sketch out a winning strategy for a particular case, and observe that the other case
        is losing because it places the other player into the winning case.
    */

    int n;
    cin >> n;
    int sum = 0, mx = 0;
    while (n--) {
        int a_i;
        cin >> a_i;
        sum += a_i;
        mx = max(mx, a_i);
    }

    if (mx > sum / 2) {
        cout << "T\n";
    } else {
        cout << (sum % 2 ? "T" : "HL") << "\n";
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
