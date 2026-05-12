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

template <typename T>
struct Multiset {
    void add(T object) {
        counts[object] += 1;
    }

    void remove(T object) {
        if (counts.find(object) == counts.end()) {
            throw std::logic_error("Object not found in multiset");
        }

        counts[object] -= 1;
        if (counts[object] == 0) {
            counts.erase(object);
        }
    }

    void add(T object, long long delta) {
        assert(delta >= 0);
        counts[object] += delta;
    }

    void remove(T object, long long delta) {
        assert(delta >= 0);
        if (counts.find(object) == counts.end() || counts[object] < delta) {
            throw std::logic_error("Not enough instances of object in multiset");
        }

        counts[object] -= delta;
        if (counts[object] == 0) {
            counts.erase(object);
        }
    }

    long long count(T object) {
        if (counts.find(object) == counts.end()) {
            return 0;
        } else {
            return counts[object];
        }
    }
    
    bool empty() {
        return counts.empty();
    }

    std::unordered_map<T, long long> counts;
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    cin >> a;

    Multiset<int> m;
    int l = 0;
    ll ans = 0;
    for (int r = 0; r < n; ++r) {
        m.add(a[r]);
        while (m.counts.size() > k) {
            m.remove(a[l++]);
        }
        ans += r - l + 1;
    }
    cout << ans << endl;
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
