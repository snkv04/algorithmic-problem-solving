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

struct Multiset {
    map<int, int> mp;

    void add(int x) {
        mp[x] += 1;
    }

    void remove(int x) {
        mp[x] -= 1;
        if (mp[x] == 0) {
            mp.erase(x);
        }
    }
};

void solve() {
    /*
    main idea:
    if alice chooses indices i, j, k such that i < j < k (so that a[i] <= a[j] <= a[k]), then
    bob's action is fixed: if a[n-1] >= 2 * a[k], then bob will take a[n-1], otherwise he will
    take a[k]. the reason why we multiply 2 to a[k] is because if bob takes a[k], then alice's
    sum decreases by a[k] and bob's sum increases by a[k]. so, we can iterate over pairs (i, j),
    and for each, find out what values of k work (meaning that a[i] + a[j] + a[k] > max(2*a[k], a[n-1])).

    generalizable ideas:
    - when selecting some elements from an array, see if the selections that you take can be fixed
    based on the relative order of your selections. for example, if you're taking 3 elements, don't
    iterate over the pairs of two random elements and find the third, but just iterate over the pairs
    of the two smallest (or two largest) elements and find the valid largest.
    - when looking at 3 values a, b, c such that a < b < c, and we're keeping track of which elements
    belong to two sets (here, that would be alice and bob), instead of "moving" c to the other set in
    the case that bob chooses c, we can keep c on the left side and just add 2*c to the right side, so
    then the comparison between the two sets is still valid but we don't actually have to modify the
    side we've already considered. more concretely, if we consider that alice's sum of values is a+b+c,
    we don't have to consider what happens when alice's sum goes to a+b because bob chose c, we can just
    add 2*c to bob's side so then alice's sum stays the same and we can treat it as whatever value it
    already is.
    */

    int n;
    cin >> n;
    vector<int> a(n); for (int i = 0; i < n; ++i) cin >> a[i];

    ll ans = 0;
    for (int i = 0; i < n-2; ++i) {
        for (int j = i+1; j < n-1; ++j) {
            int mn = a[n-1] - a[i] - a[j] + 1, mx = a[i] + a[j] - 1;
            if (mx < mn) continue;

            int l = j+1, r = n-1, left = -1;
            while (l <= r) {
                int m = (l + r) / 2;
                if (a[m] >= mn) {
                    left = m;
                    r = m-1;
                } else {
                    l = m + 1;
                }
            }
            l = j + 1; r = n-1; int right = -1;
            while (l <= r) {
                int m = (l + r) / 2;
                if (a[m] <= mx) {
                    right = m;
                    l = m+1;
                } else {
                    r = m-1;
                }
            }
            
            if (left == -1 || right == -1) {
                continue;
            }
            ans += right - left + 1;
        }
    }
    cout << ans << '\n';
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
