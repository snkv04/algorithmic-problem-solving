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
    int n, m;
    cin >> n >> m;
    int left = 0, right = 0;
    set<int> fixed_people;
    while (n--) {
        int x_i;
        cin >> x_i;
        if (x_i == -1) ++left;
        else if (x_i == -2) ++right;
        else fixed_people.insert(x_i);
    }

    int ans = max(
        left + fixed_people.size(),
        right + fixed_people.size()
    );
    if (ans >= m) {
        cout << m << '\n';
        return;
    }

    map<int, int> to_left, to_right;
    int cnt = 1;
    for (int x_i : fixed_people) {
        to_left[x_i] = cnt++;
    }
    cnt = 1;
    for (auto it = fixed_people.rbegin(); it != fixed_people.rend(); ++it) {
        to_right[*it] = cnt++;
    }
    for (int x_i : fixed_people) {
        ans = max(
            ans,
            1 + min(x_i - 1, to_left[x_i] - 1 + left) + min(m - x_i, to_right[x_i] - 1 + right)
        );
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
