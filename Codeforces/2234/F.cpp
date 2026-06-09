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
    SegmentTree(const std::vector<int> &arr) : arr(arr), n(arr.size()) {
        max_tree = vector<ll>(4 * n, -1e9);
        sum_tree = vector<ll>(4 * n, 0);
        build(1, 0, n - 1);
    }

    void build(int vertex, int left, int right) {
        if (left == right) {
            sum_tree[vertex] = max_tree[vertex] = arr[left];
            return;
        }

        int mid = left + (right - left) / 2;
        build(2 * vertex, left, mid);
        build(2 * vertex + 1, mid + 1, right);
        max_tree[vertex] = max(max_tree[2 * vertex], max_tree[2*vertex + 1]);
        sum_tree[vertex] = sum_tree[2 * vertex] + sum_tree[2 * vertex + 1];
    }

    long long _query_max(int vertex, int left, int right, int query_left, int query_right) {
        if (right < query_left || query_right < left) {
            return -1e9;
        }
        if (query_left <= left && right <= query_right) {
            return max_tree[vertex];
        }

        int mid = left + (right - left) / 2;
        return max(
            _query_max(2 * vertex, left, mid, query_left, query_right),
            _query_max(2 * vertex + 1, mid + 1, right, query_left, query_right)
        );
    }

    long long _query_sum(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return sum_tree[v];
        }

        int m = (l + r) / 2;
        return (
            _query_sum(2 * v, l, m, ql, qr) +
            _query_sum(2 * v + 1, m + 1, r, ql, qr)
        );
    }

    long long query(int left, int right, int tp) {
        if (tp) {
            return _query_sum(1, 0, n - 1, left, right);
        } else {
            return _query_max(1, 0, n - 1, left, right);
        }
    }

    void _update(int vertex, int left, int right, int idx, long long val) {
        if (left == right) {
            max_tree[vertex] = sum_tree[vertex] = val;
            return;
        }

        int mid = left + (right - left) / 2;
        if (idx <= mid) {
            _update(2 * vertex, left, mid, idx, val);
        } else {
            _update(2 * vertex + 1, mid + 1, right, idx, val);
        }
        max_tree[vertex] = max(max_tree[2 * vertex], max_tree[2*vertex + 1]);
        sum_tree[vertex] = sum_tree[2 * vertex] + sum_tree[2 * vertex + 1];
    }

    void update(int idx, long long val) {
        _update(1, 0, n - 1, idx, val);
    }

private:
    int n;
    std::vector<long long> max_tree, sum_tree;
    std::vector<int> arr;
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    for (int i = 0; i < n; ++i) a.push_back(a[i]);

    int mx = 0, mxidx = -1;
    for (int i = 0; i < n; ++i) if (a[i] > mx) { mx = a[i]; mxidx = i; }

    vector<int> nxtlen(2 * n), prvlen(2 * n);
    stack<int> stk;
    for (int i = 0; i <= 2 * n; ++i) {
        int val = (i == 2 * n) ? 1e9 : a[i];
        while (stk.size() && a[stk.top()] <= val) {
            nxtlen[stk.top()] = i - stk.top();
            stk.pop();
        }
        stk.push(i);
    }
    stk.pop();
    for (int i = 2 * n - 1; i >= -1; --i) {
        int val = i == -1 ? 1e9 : a[i];
        while (stk.size() && a[stk.top()] <= val) {
            prvlen[stk.top()] = stk.top() - i;
            stk.pop();
        }
        stk.push(i);
    }
    assert(stk.size() == 1);

    stack<pair<ll, ll>> left, right;
    ll leftsum = 0, rightsum = 0;
    auto pushleft = [&](int idx) {
        int covering = nxtlen[idx] - 1;
        while (covering) {
            leftsum -= left.top().first * left.top().second;
            covering -= left.top().second;
            left.pop();
        }
        left.push({a[idx], nxtlen[idx]});
        leftsum += 1LL * a[idx] * nxtlen[idx];
    };
    auto pushright = [&](int idx) {
        int covering = prvlen[idx] - 1;
        while (covering) {
            rightsum -= right.top().first * right.top().second;
            covering -= right.top().second;
            right.pop();
        }
        right.push({a[idx], prvlen[idx]});
        rightsum += 1LL * a[idx] * prvlen[idx];
    };
    for (int i = mxidx - 1; i >= 0; --i) pushleft(i);
    for (int i = mxidx + 1; i < n; ++i) pushright(i);

    vector<ll> ans(n, 0);
    ans[0] = leftsum + rightsum;
    for (int i = 1; i < n; ++i) {
        if (mxidx < i) {
            leftsum = rightsum = 0;
            assert(left.empty());
            right = stack<pair<ll, ll>>();

            mxidx += n;
            for (int j = mxidx - 1; j >= i; --j) {
                pushleft(j);
            }
        } else {
            // pops left
            int covering = left.top().second - 1;
            leftsum -= left.top().first * left.top().second;
            left.pop();
            if (covering) {
                stack<pair<ll, ll>> reversed;
                int idx = i;
                while (covering) {
                    reversed.push({a[idx], nxtlen[idx]});
                    covering -= nxtlen[idx];
                    idx += nxtlen[idx];
                }

                while (reversed.size()) {
                    left.push(reversed.top());
                    leftsum += reversed.top().first * reversed.top().second;
                    reversed.pop();
                }
            }

            // pushes right
            pushright(i + n - 1);
        }
        ans[i] = leftsum + rightsum;
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << "\n";
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
