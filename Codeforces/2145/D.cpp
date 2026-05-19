#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

struct SegmentTree {
private:
    int n;
    vector<ll> t;
    vector<int> a;

public:
    SegmentTree(const vector<int> &arr) {
        n = arr.size();
        a = arr;
        t.resize(4 * n);
        fill(t.begin(), t.end(), 0);
        build(1, 0, n - 1);
    }

    void build(int v, int l, int r) {
        if (l == r) {
            t[v] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(2 * v, l, m);
        build(2 * v + 1, m + 1, r);
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    ll _query(int v, int l, int r, int ql, int qr) {
        if (r < ql || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return t[v];
        }

        int m = l + (r - l) / 2;
        return _query(2 * v, l, m, ql, qr)
            + _query(2 * v + 1, m + 1, r, ql, qr);
    }

    ll query(int ql, int qr) {
        return _query(1, 0, n - 1, ql, qr);
    }

    void _update(int v, int l, int r, int idx, int val) {
        if (l == r) {
            t[v] = val;
            return;
        }

        int m = l + (r - l) / 2;
        if (idx <= m) {
            _update(2 * v, l, m, idx, val);
        } else {
            _update(2 * v + 1, m + 1, r, idx, val);
        }
        t[v] = t[2 * v] + t[2 * v + 1];
    }

    void update(int idx, int val) {
        _update(1, 0, n - 1, idx, val);
    }
};

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

vector<int> build_ans_ugly(vector<int> &lengths, int n) {
    vector<pair<int, int>> to_reverse;
    int curr_len = 0;
    for (int i = 0; i < lengths.size() - 1; ++i) {
        curr_len += lengths[i];
        pair<int, int> pushing = {curr_len, curr_len + 1};
        if (to_reverse.size() && to_reverse.back().second == pushing.first) {
            to_reverse.back().second = pushing.second;
        } else {
            to_reverse.push_back(pushing);
        }
    }

    vector<int> ans(n + 1);
    for (int i = 1; i <= n; ++i) ans[i] = i;
    for (auto [l, r] : to_reverse) {
        reverse(ans.begin() + l, ans.begin() + r + 1);
    }
    ans.erase(ans.begin());
    return ans;
}

vector<int> build_ans_clean(vector<int> &lengths, int n) {
    vector<int> ans;
    int mx = n;
    for (int len : lengths) {
        for (int i = mx - len + 1; i <= mx; ++i) {
            ans.push_back(i);
        }
        mx -= len;
    }
    return ans;
}

void solve() {
    /*
    key idea:
    - given a fixed set of split points (i.e., points i such that (i, i + 1) are an inversion),
    it's harder to reason about the number of subarrays with an inversion, and easier to reason
    about the number of subarrays without an inversion
        - on the subarrays with an inversion:
            - it's harder, because if we iterate through each split point and count the number of subarrays
            they contribute to, there'll be subarrays that are double-counted (since these sets of subarrays
            will overlap)
            - it's also O(n^2) to compute directly (just iterate over all subarrays), though this is
            less of an important point
        - on the subarrays without an inversion:
            - it's easier, because the subarrays that are free from any inversions are all grouped up between
            those split points, and these groups do not overlap, so there won't be any double-counting
            - it's O(n) to compute directly, as we go through each split point and just find the distance
            to the last one and use that, though this is less of an important point
    */

    int n, k;
    cin >> n >> k;

    int want = n * (n - 1) / 2 - k;
    vector<vector<bool>> mem(n + 1, vector<bool>(1 + want, false));
    vector<vector<pair<int, int>>> prev(n + 1, vector<pair<int, int>>(want + 1, {-1, -1}));
    mem[0][0] = true;
    for (int i = 1; i <= n; ++i) {
        for (int subarrays = 0; subarrays <= want; ++subarrays) {
            for (int len = 1; len <= i; ++len) {
                if (len * (len - 1) / 2 > subarrays) {
                    break;
                }

                if (!mem[i][subarrays] && mem[i - len][subarrays - len * (len - 1) / 2]) {
                    mem[i][subarrays] = true;
                    prev[i][subarrays] = {i - len, subarrays - len * (len - 1) / 2};
                }
            }
        }
    }
    if (!mem[n][want]) {
        cout << "0\n";
        return;
    }

    vector<int> lengths;
    pair<int, int> curr = {n, want};
    while (curr.first != 0) {
        auto previous = prev[curr.first][curr.second];
        lengths.push_back(curr.first - previous.first);
        curr = previous;
    }
    // cout << "lengths = " << lengths << endl;

    // auto ans = build_ans_ugly(lengths, n);
    auto ans = build_ans_clean(lengths, n);
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << "\n";
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
