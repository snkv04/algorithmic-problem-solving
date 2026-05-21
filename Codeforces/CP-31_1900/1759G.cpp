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
    - iterate through missing elements in decreasing order, and for each, put it in the last possible place we can
    - by iterating in decreasing order, we keep opening up new slots for us to put our current element in; if we
    iterated in increasing order, it would be difficult to tell for sure where to put our current element, but by
    going the other way, the greedy algorithm is quite clear and correct
    */

    int n;
    cin >> n;
    vector<int> b(n / 2);
    cin >> b;

    set<int> available;
    for (int i = 1; i <= n; ++i) available.insert(i);
    for (int b_i : b) available.erase(b_i);
    if (available.size() != n / 2) {
        cout << "-1\n";
        return;
    }

    vector<pair<int, int>> sorted_b;
    for (int i = 0; i < n / 2; ++i) sorted_b.push_back(make_pair(b[i], i));
    sort(sorted_b.begin(), sorted_b.end());

    vector<int> a(n / 2);
    int idx = n / 2 - 1;
    set<int> indices;
    for (auto it = available.rbegin(); it != available.rend(); ++it) {
        int num = *it;

        while (idx >= 0 && sorted_b[idx].first > num) {
            indices.insert(sorted_b[idx--].second);
        }

        if (indices.empty()) {
            cout << "-1\n";
            return;
        } else {
            int idx = *indices.rbegin();
            indices.erase(idx);
            a[idx] = num;
        }
    }

    for (int i = 0; i < n / 2; ++i) {
        cout << a[i] << ' ' << b[i] << ' ';
    }
    cout << '\n';
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
