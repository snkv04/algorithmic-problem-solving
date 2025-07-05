#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

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
    observations:
    - wlog, assume m <= n
    - if n > 2*m, then kmax = m
    - else, if diff = n-m, then kmax = diff + floor(2 * (m - diff) / 3)
        - by simplifying this, we get kmax = (m+n)/3
    - the area of the triangle where two points are on the same line and the third
    point is on a different, parallel line 2 units away is just equal to the length
    of the segment between the two points on the same line
        - this, obviously, simplifies things heavily, as expected
    - now, how would we actually get the maximum number of points for a given value
    of k?
    - if we just consider one side (say, the top side) where we repeatedly do operations
    with two points on that side and one point on the other side, without worrying about
    how many operations to do on the other side, then it seems like a plausible greedy
    strategy to just repeatedly get the two farthest points (i.e., the one on the left
    and the one on the right together)
        - it turns out that this is completely true, due to that familiar idea of overlapping
        segments, where if we have a <= b <= c <= d, then (c-a) + (d-b) = (d-a) + (c-b), so
        we might as well just unravel the points in outer pairs like an onion
    - on the other side (the bottom side), we would just select the middle point
        - this works in all cases, regardless of an even/odd number of points to use for
        operations
    - basically, this is to say that for a given number of operations on either side, the
    score gained from those operations alone is fixed, so it can actually just be precomputed
    - then, interestingly, once you realize that you're going to have to iterate over k
    anyway at some point, you can realize that for a fixed number k, if you know the number
    of operations on the top then you automatically know the number of operations on the bottom,
    so you can just find the max score across all counts of operations on the top
    - this is too slow, though. how to do it faster? well, realize that the number of points
    gained as the number of operations increases is strictly increasing, and the progressive
    increases are strictly decreasing. this means that for p operations on the top and k total
    operations (so q = k-p operations on the bottom), if we sum up the scores gotten from the
    top and bottom and call that sum s, then s will be increasing for some time and then be
    decreasing for the rest. in other words, a ternary search will one-shot this problem
    - finally, what are the ranges of possible numbers of operations? recognize that the number
    of points we need are 2p+q on the top and 2q+p on the bottom, so we can place the restriction
    of 2p+q=2p+k-p=p+k <= m as well as 
        - just for the sake of documentation, this wasn't immediately clear by the way; i tried
        to manipulate the equations in a couple of different ways before trying out this
        inequality formulation
        - keep in mind that these are not the only restrictions! for the value of p to make
        sense in the context of the problem, it also has to be non-negative and less than or
        equal to k

    main concepts in simplified solution:
    - finding the max possible number of operations given the points on the top and bottom
    - greedily selecting points to repeatedly perform the next operation on (onion-style)
    - bounding the number of operations on each of the two sides at the same time
    - performing ternary search to find max score based on number of operations on a single side
    - finding max score for each k INDEPENDENTLY of other k values
        - in some other problems, finding some optimal value for each value of some variable
        is dependent on what the optimal value was for other values of that variable
    - applying the maximum number of operations might not give the maximum score,
    because doing those operations will take up points on the other side that might have been
    used to end up with a greater score
    */

    int n, m;
    cin >> n >> m;
    vector<int> b(n), a(m);
    for (int i = 0; i < n+m; ++i) {
        if (i < n) cin >> b[i];
        else cin >> a[i-n];
    }
    if (m > n) {
        swap(m, n);
        swap(a, b);
    }

    // m <= n
    // len(a)=m, len(b)=n
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    vector<ll> scorea(1, 0), scoreb(1, 0);
    for (int i = 0; i < m/2; ++i) {
        scorea.push_back(scorea[i] + (a[m-1-i] - a[i]));
    }
    for (int i = 0; i < n/2; ++i) {
        scoreb.push_back(scoreb[i] + (b[n-1-i]-b[i]));
    }
    // print_container(scorea, "scorea = ");
    // print_container(scoreb, "scoreb = ");

    int kmax = (n > 2 * m) ? m : (m + n) / 3;
    cout << kmax << "\n";
    if (kmax) {
        for (int k = 1; k <= kmax; ++k) { // cout << "\nk = " << k << "====\n";
            // 2p+q<=m -> 2p+k-p<=m -> p <= m-k
            // 2q+p<=n -> 2k-p<=n -> p >= 2k-n
            int l = max(0, 2 * k - n), r = min(k, m-k);
            auto getscore = [&scorea, &scoreb, k](int p) {
                int q = k - p;
                // cout << "p="<<p<<" and k="<<k<<" so q="<<q<<", and we have a[p]="<<scorea[p]<<", and b[q]="<<scoreb[q]<<"\n";
                return scorea[p] + scoreb[q];
            };
            while (l <= r - 3) {
                // cout << "l = " << l << ", r = " << r << '\n';
                int roundedthird = (r - l + 1) / 3;
                int m1 = l+roundedthird, m2 = r-roundedthird;
                if (getscore(m1) <= getscore(m2)) {
                    l = m1;
                } else {
                    r = m2;
                }
            }

            ll maxscore = -1;
            for (int i = l; i <= r; ++i) {
                maxscore = max(maxscore, getscore(i));
            }
            cout << maxscore << " ";
        }
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
