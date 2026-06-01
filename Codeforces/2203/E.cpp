#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 998244353;
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

ll mod_pow(ll b, ll e) {
    if (e == 0) return 1;
    if (e % 2) return mod_pow(b, e - 1) * b % MOD;
    else return mod_pow(b * b % MOD, e / 2) % MOD;
}

ll mod_inv(ll x) {
    return mod_pow(x, MOD - 2);
}

ll mod_div(ll n, ll d) {
    return n * mod_inv(d) % MOD;
}

struct SegmentTree {
    SegmentTree(int n) : n(n) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
    }

    SegmentTree(const std::vector<int> &arr) : arr(arr), n(arr.size()) {
        tree.resize(4 * n);
        std::fill(tree.begin(), tree.end(), 0);
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

    long long _query(int vertex, int left, int right, int query_left, int query_right) {
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
        if (left > right) return 0;
        return _query(1, 0, n - 1, left, right);
    }

    void _update(int vertex, int left, int right, int idx, long long val) {
        if (left == right) {
            tree[vertex] = val;
            return;
        }

        int mid = left + (right - left) / 2;
        if (idx <= mid) {
            _update(2 * vertex, left, mid, idx, val);
        } else {
            _update(2 * vertex + 1, mid + 1, right, idx, val);
        }
        tree[vertex] = tree[2 * vertex] + tree[2 * vertex + 1];
    }

    void update(int idx, long long val) {
        _update(1, 0, n - 1, idx, val);
    }

    int walk(int want) {
        int v = 1, l = 0, r = n - 1;
        // cout << "want = " << want << endl;
        assert(tree[v] >= want);
        assert(want);
        while (l != r) {
            int m = (l + r) / 2;
            if (tree[2 * v] < want) {
                want -= tree[2 * v];
                v = 2 * v + 1;
                l = m + 1;
            } else {
                v = 2 * v;
                r = m;
            }
        }
        return l;
    }

private:
    int n;
    std::vector<long long> tree;
    std::vector<int> arr;
};

ll getleft(int actidx, int totalact, int m, SegmentTree &cnt, SegmentTree &sum, map<ll, ll> &decompressed) {
    if (actidx <= 2) return 0;  // base case

    int bactidx = actidx - 1;
    int btrueidx = cnt.walk(bactidx);  // "trueidx" = idx among elements of length-m array
    ll b = decompressed[btrueidx];
    assert(bactidx - 1 == cnt.query(0, btrueidx - 1));
    return b * (bactidx - 1) - sum.query(0, btrueidx - 1);
}

ll getright(int actidx, int totalact, int m, SegmentTree &cnt, SegmentTree &sum, map<ll, ll> &decompressed) {
    if (actidx >= totalact - 1) return 0;  // base case

    int bactidx = actidx + 1;
    int btrueidx = cnt.walk(bactidx);
    ll b = decompressed[btrueidx];
    assert(totalact - bactidx == cnt.query(btrueidx + 1, m - 1));
    return sum.query(btrueidx + 1, m - 1) - b * (totalact - bactidx);
}

void solve() {
    int m;
    cin >> m;
    vector<ll> a(m);
    cin >> a;

    map<ll, ll> compressed, decompressed;
    for (int i = 0; i < m; ++i) {
        compressed[a[i]] = -1;
    }
    int idx = 0;
    for (auto &[k, v] : compressed) {
        v = idx;
        decompressed[idx++] = k;
    }

    SegmentTree cnt(m), sum(m);
    auto print_st = [&](SegmentTree &st) {
        for (int i = 0; i < m; ++i) {
            cout << st.query(i, i) << " ";
        }
        cout << "\n";
    };
    for (int i = 1; i <= m; ++i) {
        // DON'T USE AN INT TO STORE A LONG LONG!
        // the bug is always some goofy shit bruh.
        ll val = a[i - 1], idx = compressed[val];
        cnt.update(idx, 1);
        sum.update(idx, val);
        // print_st(cnt);
        if (i <= 2) continue;

        int l = 2, r = i - 1, bestactidx = 2;  // "actidx" = idx among activated objects/cards
        while (l <= r) {
            int mid = (l + r) / 2;
            ll ifleft = getleft(mid, i, m, cnt, sum, decompressed);
            ll ifright = getright(mid, i, m, cnt, sum, decompressed);
            if (ifright >= ifleft) {
                bestactidx = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        ll best = min(
            max(getleft(bestactidx, i, m, cnt, sum, decompressed), getright(bestactidx, i, m, cnt, sum, decompressed)),
            max(getleft(bestactidx + 1, i, m, cnt, sum, decompressed), getright(bestactidx + 1, i, m, cnt, sum, decompressed))
        );
        best %= MOD;
        // cout << "before dividing, best = " << best << endl;
        best = mod_div(best, i - 2);
        cout << best << "\n";
    }
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
