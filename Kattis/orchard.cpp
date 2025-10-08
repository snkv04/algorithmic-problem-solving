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

struct State {
    vector<int> counts;
    int steps;

    bool operator==(const State &other) const {
        if (steps != other.steps) return false;
        for (int i = 0; i < 4; ++i) if (counts[i] != other.counts[i]) return false;
        return true;
    }
};

struct Hasher {
    size_t operator()(const State &s) const {
        const vector<int> &c = s.counts;
        return 1000 * c[0] + 200 * c[1] + 40 * c[2] + 8 * c[3] + s.steps;
    }
};

unordered_map<State, double, Hasher> mem;

double recurse(vector<int> &counts, int steps) {
    /*
    - observe that because there are not any special rules to distinguish each fruit from each other,
    the counts being [1, 2, 2, 3] does not change the probability of ending in a win compared to the
    counts being [2, 3, 2, 1]. in other words, these probabilities are symmetric, and so states like
    these are equivalent when the multisets of counts are equivalent. so, to eliminate redundant computation
    when the outcomes of those two states will just end up with the same probabilities, we can just sort
    the counts.
    */

    int sum = 0;
    for (int c : counts) sum += c;
    if (sum == 0) return 1.0;
    if (steps == 0) return 0.0;
    State state{counts, steps};
    if (mem.find(state) != mem.end()) return mem[state];

    double result = 0.0;
    int possibilities = 2;  // raven and fruit
    int mx = 0, mx_cnt = 0;
    for (int i = 0; i < 4; ++i) {
        if (counts[i]) {
            ++possibilities;
        }

        if (counts[i] > mx) {
            mx = counts[i];
            mx_cnt = 1;
        } else if (counts[i] == mx) {
            mx_cnt += 1;
        }
    }

    result += (1.0 / possibilities) * recurse(counts, steps - 1);
    for (int i = 0; i < 4; ++i) {
        if (counts[i]) {
            vector<int> copy = counts;
            copy[i] -= 1;
            sort(copy.begin(), copy.end());
            result += (1.0 / possibilities) * recurse(copy, steps);
        }
    }
    for (int i = 0; i < 4; ++i) {
        if (counts[i] == mx) {
            vector<int> copy = counts;
            copy[i] -= 1;
            sort(copy.begin(), copy.end());
            result += (1.0 / (possibilities * mx_cnt)) * recurse(copy, steps);
        }
    }
    
    mem[state] = result;
    return result;
}

void solve() {
    int r, g, b, y, s;
    cin >> r >> g >> b >> y >> s;
    vector<int> counts = {r, g, b, y};
    sort(counts.begin(), counts.end());
    cout << recurse(counts, s) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
