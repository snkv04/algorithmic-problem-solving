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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    for (int i = 0; i < n-1; ++i) {
        if (abs(a[i]-a[i+1]) > 1) {
            cout << "0\n";
            return;
        }
    }

    bool eq = true;
    for (int i = 0; i < n-1; ++i) {
        if (a[i] != a[i+1]) {
            eq = false;
            break;
        }
    }
    if (eq) {
        if (n % 2) {
            if (a[0] == (n + 1) / 2) {
                cout << "2\n";
            } else {
                cout << "0\n";
            }
        } else {
            if (a[0] == n / 2 || a[0] == (n / 2) + 1) {
                cout << "1\n";
            } else {
                cout << "0\n";
            }
        }
        return;
    }

    int i = 0;
    vector<char> s(n, ' ');
    while (i < n-1 && a[i] == a[i+1]) ++i;
    for ( ; i < n-1; ++i) {
        if (a[i] < a[i+1]) {
            s[i] = s[i+1] = 'L';
        } else if (a[i] > a[i+1]) {
            s[i] = s[i+1] = 'R';
        } else {
            s[i+1] = (s[i] == 'L') ? 'R' : 'L';
        }
    }
    for (int j = n-2; j >= 0; --j) {
        if (s[j] == ' ') {
            s[j] = (s[j+1] == 'L') ? 'R' : 'L';
        }
    }
    // print_container(s, "s = ");

    // check string
    vector<int> pref(n), suf(n);
    for (int i = 0; i < n; ++i) {
        pref[i] = s[i] == 'L';
        if (i) pref[i] += pref[i-1];
    }
    for (int i = n-1; i >= 0; --i) {
        suf[i] = s[i] == 'R';
        if (i < n-1) suf[i] += suf[i+1];
    }
    // print_container(pref, "pref = ");
    // print_container(suf, "suf = ");

    bool works = true;
    for (int i = 0; i < n; ++i) {
        int ls = i == 0 ? 0 : pref[i-1];
        int rs = i == n-1 ? 0 : suf[i+1];
        if (a[i] != 1 + ls + rs) {
            works = false;
            break;
        }
    }
    cout << (works ? 1 : 0) << "\n";
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
