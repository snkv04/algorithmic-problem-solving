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
    /*
    main ideas:
    - naturally, when b is spliced into a to create c, we want to have b in nonincreasing order so that
    b does not create any new increasing subsequences from its own elements.
    - if we want to insert b_i into a, then inserting it after an a_j that is <= b_i is bad, because then
    we can possibly use both a_j and b_i in a LIS that a_j was already in. so, it would be best to put
    b_i before a_j. we basically just repeat the same logic, putting each b_i into a location before an
    a_j while b_i >= a_j. if there's no a_j in the whole array that's <= b_i, then it's good to put b_i
    at the end of the array, so then it can't be used in an LIS with any element from a.
        - also, since we're going through b in descending order, we know that if b_i < a_j, then we also
        know that b_{i+1} < a_j, so we want to hold off on inserting ALL of them (all k in [i, m-1]). on
        the other hand, if we were maybe going through b in random order or increasing order, then even
        if b_i shouldn't be placed at the current index of a, maybe b_{i+1} could be. in that case, the
        current pointer in b gives us less information; the way i'm doing it, if the index is currently
        somewhere in b, then we know that all the elements that we could process from b (given the current
        index in a) have already been processed. that is why this is a "greedy" scheme; we always put the
        best (greatest) element from b next, and among the two elements we are looking at from a and b,
        we always put the greatest one next. this minimizes the LIS, given that the LIS length from a is
        already fixed.
    - in short, after sorting b in non-increasing order, we are basically greedily merging a and b using
    a pointer for each array, always inserting whichever element is greater before pushing the pointer
    for that array forward.
    */

    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n+m; ++i) {
        if (i < n) cin >> a[i];
        else cin >> b[i-n];
    }

    sort(b.begin(), b.end(), [](const int &a, const int &b) {return a > b;});
    int i = 0, j = 0;
    vector<int> ans;
    while (i + j < n + m) {
        if (i == n) {
            ans.push_back(b[j++]);
        } else if (j == m) {
            ans.push_back(a[i++]);
        } else {
            while (j < m && b[j] >= a[i]) {
                ans.push_back(b[j++]);
            }
            ans.push_back(a[i++]);
        }
    }
    for (int num : ans) cout << num << " ";
    cout << '\n';
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
