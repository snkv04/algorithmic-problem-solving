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

template <typename T>
std::ostream& operator<<(std::ostream &os, const vector<T> &c) {
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
    vector<pair<ll, ll>> a;
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        a.push_back({ai, i+1});
    }
    if (m > n/2) {
        cout << "-1\n";
        return;
    }
    if (m == 0) {
        sort(a.begin(), a.end());
        int i = n-2;
        ll sum = 0;
        while (sum < a[n-1].first && i >= 0) {
            sum += a[i].first;
            --i;
        }
        if (sum < a[n-1].first) {
            cout << "-1\n";
        } else {
            cout << n-1 << "\n";
            for (int j = 0; j <= i; ++j) {
                cout << a[j].second << " " << a[j+1].second << "\n";
            }
            for (int j = i+1; j <= n-2; ++j) {
                cout << a[j].second << " " << a[n-1].second << "\n";
            }
        }
        return;
    }

    sort(a.begin(), a.end());
    vector<pair<ll, ll>> b(a.begin() + n-m, a.end());
    a.erase(a.begin() + n - m, a.end());
    reverse(a.begin(), a.end());

    cout << n-m << '\n';
    while (b.size() < a.size()) {
        cout << a[a.size()-1].second << " " << a[a.size()-2].second << '\n';
        a.pop_back();
    }
    for (int i = 0; i < a.size(); ++i) {
        cout << b[i].second << " " << a[i].second << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
