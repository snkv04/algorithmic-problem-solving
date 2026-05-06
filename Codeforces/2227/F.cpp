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

struct Lazy {
    Lazy(int n) : n(n) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
        pending.resize(4 * n);
        std::fill(pending.begin(), pending.end(), 0);
    }

    Lazy(const std::vector<int> &arr) : arr(arr), n(arr.size()) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
        pending.resize(4 * n);
        std::fill(pending.begin(), pending.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int vertex, int left, int right) {
        if (left == right) {
            tree[vertex] = arr[left];
            return;
        }

        int mid = left + (right - left) / 2;
        build(2 * vertex, left, mid);
        build(2 * vertex + 1, mid + 1, right);
        tree[vertex] = tree[2 * vertex] + tree[2 * vertex + 1];
    }

    void push_down(int vertex, int left, int right) {
        if (pending[vertex] != 0) {
            tree[vertex] += pending[vertex] * (right - left + 1);

            if (left != right) {
                pending[2 * vertex] += pending[vertex];
                pending[2 * vertex + 1] += pending[vertex];
            }

            pending[vertex] = 0;
        }
    }

    long long _query(int vertex, int left, int right, int query_left, int query_right) {
        push_down(vertex, left, right);

        if (right < query_left || query_right < left) {
            return 0;
        }
        if (query_left <= left && right <= query_right) {
            return tree[vertex];
        }

        int mid = left + (right - left) / 2;
        return _query(2 * vertex, left, mid, query_left, query_right) +
            _query(2 * vertex + 1, mid + 1, right, query_left, query_right);
    }

    long long query(int left, int right) {
        return _query(1, 0, n - 1, left, right);
    }

    void _update(int vertex, int left, int right, int query_left, int query_right, long long val) {
        push_down(vertex, left, right);

        if (right < query_left || query_right < left) {
            return;
        }
        if (query_left <= left && right <= query_right) {
            pending[vertex] += val;
            push_down(vertex, left, right);
            return;
        }

        int mid = left + (right - left) / 2;
        _update(2 * vertex, left, mid, query_left, query_right, val);
        _update(2 * vertex + 1, mid + 1, right, query_left, query_right, val);
        tree[vertex] = tree[2 * vertex] + tree[2 * vertex + 1];
    }

    void update(int left, int right, long long val) {
        _update(1, 0, n - 1, left, right, val);
    }

private:
    int n;
    std::vector<long long> tree, pending;
    std::vector<int> arr;
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    ll initial = 0;
    Lazy final_pos(n + 1);
    for (int i = 1; i <= n; ++i) {
        int idx = n - i;
        int height = a[idx];
        final_pos.update(1, height, 1);
        initial += (((ll) height) * i) - final_pos.query(1, height);
    }
    // cout << initial << endl;

    ll additional = 0;
    vector<pair<int, int>> sorted;
    for (int i = 0; i < n; ++i) sorted.push_back(make_pair(-a[i], i));  // descending height, then ascending index
    sort(sorted.begin(), sorted.end());
    Lazy seen(n);  // don't really need lazy prop, but might as well use the same class
    for (auto [height, i] : sorted) {
        seen.update(i, i, 1);
        additional = max(additional, seen.query(0, i) - 1);
    }
    
    ll ans = initial + additional;
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
