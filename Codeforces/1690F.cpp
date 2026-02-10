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
    generalized main ideas:
    - permutation can be broken into cycles
    - each cycle has some number of steps after which it has returned to its original sequence; we want to take
    the LCM of this value across cycles
        - when i say "step", i'm talking about a single cyclic shift (such as to the right)
    - however, each cycle can have different numbers of steps after which it returns to its original sequence;
    key idea is that if it returns to its original sequence after k_1 and after k_2 steps, then it also returns to
    its original sequence after gcd(k_1, k_2) steps
    */

    int n;
    cin >> n;
    string s;
    vector<int> p(n);
    cin >> s; for (int i = 0; i < n; ++i) { cin >> p[i]; --p[i]; }

    vector<bool> visited(n, false);
    ll ans = 1;
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int curr = i;
            vector<char> cycle;
            while (!visited[curr]) {
                cycle.push_back(s[curr]);
                visited[curr] = true;
                curr = p[curr];
            }

            vector<int> divisors;
            for (int j = 1; j <= cycle.size(); ++j) {
                if (cycle.size() % j == 0) divisors.push_back(j);  // causes overall O(t * n * sqrt(n))
            }

            int required = -1;
            for (int d : divisors) {
                bool works = true;
                for (int idx = 0; idx < cycle.size(); ++idx) {
                    if (cycle[idx] != cycle[idx % d]) {
                        works = false;
                        break;
                    }
                }
                if (works) {
                    required = d;
                    break;  // just take the smallest such divisor, because of the above theorem
                }
            }
            ans = lcm(ans, required);
        }
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
