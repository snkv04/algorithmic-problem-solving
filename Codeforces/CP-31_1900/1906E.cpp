#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int MOD = (int) 1e9 + 7; // 998244353;
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
        - we have an array C
        - we want to find two subsequences of C (whose union is C) such that if they're merged together,
        using the same algo in merge sort, then they result in C
    - observations:
        - it's clear that any strictly decreasing segment in C must have all its elements come from the
        same array (A or B).
            - why? suppose all previous elements in C (as well as the corresponding elements in A and B)
            have already been processed. if some of that segment came from A and some of it came from B,
            then merging it would put those items out of order into C, which contradicts the definition
            of C. so they have to come from the same place.
        - so, we can segment the given array C into decreasing segments, where all elements in a segment
        are pushed into C all together.
            - think of it as a condensed or abstracted array.
        - then, observe that if we view each segment as defined by its starting element, then we can
        actually repeatedly find more decreasing segments like this. we can run the segmenting algo again.
        - the point at which this algorithm converges (no more segments are joined together) is when each
        element in the original array has its segment contain EVERYTHING until the next larger element.
            - basically monotonic stack-able.
        - observe that this new array is strictly increasing. then we can just run standard merge sort,
        except each element has a length. to make sure that we can take a subset whose length equals N,
        we just use a knapsack.
    - solution:
        - segment the array into [c_i, c_{i+1}, ..., c_{j-1}), where j is the first index after i where
        c_j > c_i.
        - find out if we can take a subset of the segments whose length equals N using knapsack. if no,
        then there's no solution.
        - take a subset of these segments whose length equals N, and set the combination of these segments
        to be A. the other segments will be B.
    - interesting ideas:
        - if we repeatedly join together elements that form a decreasing subarray, and then run it again
        and again, the point at which we can't do that anymore is when the elements are strictly increasing.
        that happens when the segments stretch until the "next larger element".
        - when using knapsack to join together a bunch of objects to form some sum, make sure that we only
        update the object used at sum i if possible[i] is false. otherwise, we might reuse the same object
        multiple times on the chain to 0.
    */

    // reads in the input
    int n;
    cin >> n;
    vector<int> c(2 * n);
    cin >> c;

    // breaks it into segments
    vector<pair<int, int>> segments;
    int start = 0;
    for (int i = 0; i < 2 * n; ++i) {
        if (i == 2 * n - 1 || c[i + 1] > c[start]) {
            segments.push_back(make_pair(start, i - start + 1));
            start = i + 1;
        }
    }

    // runs a knapsack to find out what segment to use at each length to make the overall sum equal to 0
    vector<bool> possible(n + 1, false);
    vector<int> seg(n + 1, -1);
    possible[0] = true;
    // iterate through segments backwards, so following the chain moves you forward
    for (int i = segments.size() - 1; i >= 0; --i) {
        auto [start_idx, length] = segments[i];
        for (int j = n; j >= length; --j) {
            if (
                possible[j - length] &&  // can reach the previous length
                !possible[j]             // don't want to use this segment if can use another previous one
            ) {
                possible[j] = true;
                seg[j] = start_idx;
            }
        }
    }
    if (!possible[n]) {
        cout << "-1\n";
        return;
    }
    // cout << "segments = " << segments << endl;
    // cout << "possible = " << possible << endl;
    // cout << "seg = " << seg << endl;

    // builds the array A from the knapsack
    map<int, int> available;
    for (auto [start_idx, length] : segments) available[start_idx] = length;
    int curr = n;
    vector<int> a;
    while (curr != 0) {
        int start_idx = seg[curr];
        int length = available[start_idx];
        for (int i = start_idx; i < start_idx + length; ++i) {
            a.push_back(c[i]);
        }
        curr -= length;
        available.erase(start_idx);
    }

    // builds the array B from the unused segments in A
    vector<int> b;
    for (auto [start_idx, length] : available) {
        for (int i = start_idx; i < start_idx + length; ++i) {
            b.push_back(c[i]);
        }
    }

    // outputs both
    for (auto &v : {a, b}) {
        for (int i = 0; i < n; ++i) cout << v[i] << ' ';
        cout << '\n';
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
