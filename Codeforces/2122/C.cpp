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

template <typename T, size_t N>
std::ostream& operator<<(std::ostream &os, const std::array<T, N> &a) {
    os << "(";
    for (int i = 0; i < N; ++i) {
        if (i) os << ", ";
        os << a[i];
    }
    os << ")";
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

ll taxi(array<int, 3> &a, array<int, 3> &b) {
    return max(a[0]-b[0], b[0]-a[0]) + max(a[1]-b[1], b[1]-a[1]);
}

void solve() {
    int n;
    cin >> n;
    vector<array<int, 5>> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i][0] >> points[i][1];
        points[i][2] = i + 1;
    }

    sort(points.begin(), points.end());
    for (int i = 0; i < n; ++i) {
        points[i][3] = (i >= (n / 2));
    }
    sort(points.begin(), points.end(), [](const array<int, 5> &a, const array<int, 5> &b) {
        return a[1] < b[1];
    });
    for (int i = 0; i < n; ++i) {
        points[i][4] = (i >= (n / 2));
    }

    set<int> q1, q2, q3, q4;
    for (int i = 0; i < n; ++i) {
        int idx = points[i][2];
        if (points[i][3]) {
            if (points[i][4]) {
                q1.insert(idx);
            } else {
                q4.insert(idx);
            }
        } else {
            if (points[i][4]) {
                q2.insert(idx);
            } else {
                q3.insert(idx);
            }
        }
    }

    while (q1.size()) {
        cout << *q1.begin() << " " << *q3.begin() << "\n";
        q1.erase(q1.begin());
        q3.erase(q3.begin());
    }
    while (q2.size()) {
        cout << *q2.begin() << " " << *q4.begin() << "\n";
        q2.erase(q2.begin());
        q4.erase(q4.begin());
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
