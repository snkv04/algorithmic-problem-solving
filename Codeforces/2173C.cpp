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

bool check(int d, int k, set<int> &a) {
    // cout << "checking " << d << " for " << *a.begin() << endl;
    for (int i = d; i <= k; i += d) {
        if (a.find(i) == a.end()) {
            return false;
        }
    }
    return true;
}

void solve() {
    int n, k;
    cin >> n >> k;
    set<int> a;
    while (n--) {
        int ai;
        cin >> ai;
        a.insert(ai);
    }

    set<int> b, covered;
    bool works = true;
    for (int ai : a) {
        if (covered.find(ai) != covered.end()) continue;

        bool found = false;
        int rt = sqrt(ai);
        for (int d = 1; d <= rt; ++d) {
            if (ai % d == 0) {
                for (int div : vector<int>({d, ai / d})) {
                    if (check(div, k, a)) {
                        for (int i = div; i <= k; i += div) {
                            covered.insert(i);
                        }
                        b.insert(div);
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
        }

        if (!found) {
            // cout << "didn't find div for " << ai << ", when a is ";
            // for (int num : a) cout << num << " ";
            // cout << endl;
            works = false;
            break;
        }
    }

    if (works) {
        cout << b.size() << '\n';
        for (int bi : b) cout << bi << " ";
        cout << "\n";
    } else {
        cout << "-1\n";
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
