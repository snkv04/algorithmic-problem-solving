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

void solve() {
    /*
    - problem:
        - we have a bunch of layers. for each layer, we have a set of possible (x, y) pairs of empty space,
        where everything else is not empty (on that layer)
        - across all ways to pick the (x, y) segment from each layer,
        find the maximum overlap of the chosen segments across all layeres
    - solution:
        - let right_bound be a value such that our "window" (the overlap of segments) has its right end
        be <= right_bound
            - we can enforce this by always having a segment whose right bound is equal to right_bound,
            so then our inequality turns to equality
        - then, we can sweep right_bound from right to left, and for each value of right_bound, we get the
        segment from every layer whose right end is minimal but still >= right_bound
        - knowing all the segments that are active, we can find the answer for that segment selection by
        having all the left ends of active segments and right ends of active segments in multisets, and
        taking min of rights minus max of lefts
    - details:
        - given our definition of right_bound, there are 2 main strategies to go about picking segments
        from each layer:
            - (1) for each layer, we take the segment whose right end is maximal but <= right_bound
                - (in terms of correctness, it doesn't matter whether we move right_bound to the left or right,
                but moving it right is easier to implement)
            - (2) for each layer, we take the segment whose right end is minimal but >= right_bound
                - (in terms of correctness, it doesn't matter whether we move right_bound to the left or right,
                but moving it left is easier to implement)
            - why is the second optimal and the first isn't?
                - well, given the case that i drew, it's obvious there are counterexamples to the first.
                - think of it like this. we are restricting our intersection to be to the left (or at) of a right bound.
                there is no reason why the intersection has to be as close to the bound (as much to the right) as
                possible if all selected segments are to the left of the bound; it could be better to have the
                intersection more to the left. however, if all selected segments are to the right (specifically,
                their right ends are to the right) of our bound, then since the intersection will only be to the
                left by design, it's ALWAYS best to make everything as close to the bound (as much to the left)
                as possible.
                - in simpler terms, if our target is to the left of a bound and all choices are to the right, we
                want to pull our choices to the left. however, if all choices are to the left, it's hard to do some
                greedy algorithm to decide which choices we pick; pulling our choices to the right isn't necessarily
                optimal.
    - generalized ideas:
        - can maintain the "active" or "chosen" choices/objects in a data structure, especially one that is
        easy to add to/remove from (like a random-access data structure, such as an ordered set/multiset)
    */

    // reads in all inputs
    int n;
    cin >> n;
    vector<array<int, 3>> all_gaps;
    vector<vector<pair<int, int>>> layer_gaps(n);
    for (int i = 0; i < n; ++i) {
        int k, x1, x2;
        cin >> k >> x1 >> x2;

        vector<int> l(k);
        cin >> l;
        int sum = std::accumulate(l.begin(), l.end(), 0);
        int gap = x2 - x1 - sum;

        int left = x1;
        layer_gaps[i].push_back(make_pair(left, left + gap));
        all_gaps.push_back({i, left, left + gap});
        for (int j = 0; j < k; ++j) {
            left += l[j];
            layer_gaps[i].push_back(make_pair(left, left + gap));
            all_gaps.push_back({i, left, left + gap});
        }
        layer_gaps[i].push_back(make_pair(2e9, 2e9));
    }
    sort(all_gaps.begin(), all_gaps.end(), [](const array<int, 3> &a, const array<int, 3> &b) {
        return a[2] < b[2];
    });
    reverse(all_gaps.begin(), all_gaps.end());

    // sets up data structures
    multiset<int> lefts, rights;
    vector<int> idx(n);
    for (int i = 0; i < n; ++i) {
        idx[i] = layer_gaps[i].size() - 1;
        auto p = layer_gaps[i].back();
        lefts.insert(p.first);
        rights.insert(p.second);
    }

    // sweeps right bound from right to left by jumping from right end of gap to right end of gap (because
    // values in the middle won't matter, since the set of gaps that are active won't change)
    int ans = 0;
    for (auto [i, l, r] : all_gaps) {
        // deactivates the old gap for the layer we're updating
        auto curr = layer_gaps[i][idx[i]];
        lefts.erase(lefts.find(curr.first));
        rights.erase(rights.find(curr.second));

        // activates the new gap
        --idx[i];
        assert(layer_gaps[i][idx[i]].first == l);
        assert(layer_gaps[i][idx[i]].second == r);
        lefts.insert(l);
        rights.insert(r);

        // updates answer
        ans = max(
            ans,
            *rights.begin() - *lefts.rbegin()
        );
    }
    cout << ans << "\n";
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
