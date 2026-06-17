#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = 1e9 + 7;  // 998244353;
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

template <typename T1, typename T2>
std::istream& operator>>(std::istream &is, std::pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}

template <typename T, size_t N>
std::istream& operator>>(std::istream &is, std::array<T, N> &a) {
    for (size_t i = 0; i < N; ++i) {
        is >> a[i];
    }
    return is;
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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;
    a.insert(a.begin(), 0);

    vector<ll> pre(n + 1, 0), pre_lengths = pre, pre_blocks = pre, pre_first_block = pre;
    for (int i = 1; i <= n; ++i) {
        pre[i] = pre[i - 1] + a[i];
        pre_lengths[i] = pre_lengths[i - 1] + (n + 1 - i);
        pre_first_block[i] = pre_first_block[i - 1] + pre[i];
    }
    for (int i = 1; i <= n; ++i) {
        ll length = n + 1 - i;
        ll block = pre_first_block[n] - pre_first_block[i - 1] - (pre[i - 1] * length);
        // cout << "i = " << i << ", block sum = " << block << endl;
        pre_blocks[i] = pre_blocks[i - 1] + block;
    }
    // cout << "pre = " << pre << endl;
    // cout << "pre_lengths = " << pre_lengths << endl;
    // cout << "pre_blocks = " << pre_blocks << endl;
    // cout << "pre_first_block = " << pre_first_block << endl;

    int q;
    cin >> q;
    auto get_prefix = [&](int block, int len) {
        int additional = block - 1;
        ll res = pre_first_block[len + additional];
        res -= pre_first_block[additional];
        res -= pre[additional] * len;
        return res;
    };
    auto get_suffix = [&](int block, int len) {
        int block_len = pre_lengths[block] - pre_lengths[block - 1];
        int pre_len = block_len - len;
        return pre_blocks[block] - pre_blocks[block - 1] - get_prefix(block, pre_len);
    };
    while (q--) {
        ll l, r;
        cin >> l >> r;

        auto find_block = [&](ll idx) {
            ll lo = 1, hi = n, block = -1;
            while (lo <= hi) {
                ll mid = (lo + hi) / 2;
                if (pre_lengths[mid] >= idx) {
                    block = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            return block;
        };
        int lblock = find_block(l), rblock = find_block(r);
        // cout << "l = " << l << ", r = " << r << ", lblock = " << lblock << ", rblock = " << rblock << endl;

        if (lblock == rblock) {
            int l_pre_len = l - 1 - pre_lengths[lblock - 1];
            int r_pre_len = r - pre_lengths[lblock - 1];
            ll ans = get_prefix(lblock, r_pre_len) - get_prefix(lblock, l_pre_len);
            cout << ans << endl;
        } else {
            int r_pre_len = r - pre_lengths[rblock - 1];
            int l_suf_len = pre_lengths[lblock] - l + 1;
            ll ans = pre_blocks[rblock - 1] - pre_blocks[lblock];
            ans += get_prefix(rblock, r_pre_len);
            ans += get_suffix(lblock, l_suf_len);
            cout << ans << endl;
        }
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
