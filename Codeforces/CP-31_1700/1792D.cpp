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
void print_container(const Container &c, string prefix = "", string suffix = "\n", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << suffix;
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

int longest_common_prefix(vector<int> &a, vector<int> &b) {
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) return i;
    }
    return a.size();
}

void solve() {
    /*
    - across all j, we want to find the max value of LCP(a_i * a_j, I), where I is the identity permutation
    and i is fixed for each permutation. suppose that LCP(a_i * a_j, I) = k. then
    a_i * a_j = [1, 2, ..., k, a_j[a_i[k+1]], ..., a_j[a_i[n]]]. recognize that p * q can basically be written
    as q[p] (since p provides the input indices, whereas a permutation q alone is q = q[I]), so then
    we can write a_j[a_i] = [1, 2, ..., k, a_j[a_i[k+1]], ..., a_j[a_i[n]]], and by taking the inverse, we get
    a_i = a_j^-1[1, 2, ..., k, a_j[a_i[k+1]], ..., a_j[a_i[n]]]
        = [a_j^-1[1], a_j^-1[2], ..., a_j^-1[k], a_i[k+1], ..., a_i[n]]. since our goal is to maximize k,
    we want to find some a_j whose inverse has as long of a shared prefix with a_i as possible. that is why
    we invert all the permutations, and search through these inverses for each a_i.
        - this all makes sense, but only one part is not immediately intuitive. given that we have
        a_i * a_j ~ I (where ~ means that we are trying to get the LHS to approximate the RHS by maximizing
        the LCP), we have two choices: we can either frame the problem as a_j = a_i^-1 * I, meaning we want
        to find an a_j that has the LCP with a_i's inverse, or frame the problem as a_i = I * a_j^-1, meaning
        that we want to find an a_j whose inverse has the LCP with a_i. the question is, why do we go with the
        second framing and not the first? well, what does p * q really mean? p is basically the input since it
        provides the indices, and q is basically a function that takes p as input and returns a new permutation.
        so, logically, it makes more sense to invert q since q is a function than to invert p which is essentially
        just a vector of input values. in this case, q is a_j. so, we take the equation (or approximation)
        a_i * a_j = a_j[a_i] ~ I, and invert the function a_j on the outside to get a_i ~ a_j^-1[I] = I * a_j^-1.
    
    generalizable ideas:
    - well, the idea of a permutation inverse
    - if a bunch of arrays or strings are lexicographically sorted, then given a string a_i, the string with
    the longest common prefix to a_i will be the one that is either equal to it (obviously), right before, or
    right after.
        - this is intuitive, but how can this be proven? suppose that among all the strings a_j, the
        maximum LCP with a_i (let's say the a_j resulting in this is a_x) is of length k. this means that for
        positions p <= k, a_x[p] = a_i[p], and a_x[k+1] != a_i[k+1]. note that for one such value of a_x,
        if a_x compares as less than a_i, then a_x[k+1] < a_i[k+1], and as a_j becomes less and less from
        a_x, the position at which a_j differs from a_i will decrease. if a_x > a_i and we look at the a_j
        values starting from a_x and increasing, then the position at which a_j differs from a_i will also
        decrease. in other words, given that the a_j strings are sorted, the LCP with a_i for each of them
        (if all of these LCP values are placed into a corresponding list) will be effectively unimodal, so
        nondecreasing for some time and then nonincreasing for some time. so, the only two strings that we
        need to check for the LCP with a_i are the max a_j such that a_j <= a_i and the min a_j such that
        a_j >= a_i.
        - example of needing to check both: if a_i = "14352", then if the strings being searched are
        "14523" and "13245", then we need to look at the first a_j that is > a_i to get the max LCP.
        if the strings being searched are "14253" and "15234", then we need to look at the last a_j that
        is < a_i to get the max LCP.
    - this is more of a language-specific piece of information than a conceptual piece of information, but
    we can use std::lower_bound on any container by passing in 2 iterators, though it runs binary search
    so we kind of have to ensure that the container is sorted beforehand otherwise we'll just get useless
    outputs from it.
        - this is kind of just review, but how to use std::lower_bound to check both the floor and ceil?
        if a perfect match exists, then lower_bound will get us there. if it doesn't, then lower_bound
        will give us the same as upper_bound (the lowest one that is strictly higher). the iterator
        right before the one returned by lower_bound will be the highest one that is strictly lower.
    */

    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m)), sorted(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int aij;
            cin >> aij;
            --aij;
            a[i][j] = aij;
            // sorted[i][j] = aij;
            sorted[i][aij] = j;
        }
    }
    sort(sorted.begin(), sorted.end());
    // cout << "====\nsorted:\n";
    // for (int i = 0; i < n; ++i) {
    //     for (int j = 0; j < m; ++j) {
    //         cout << sorted[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "====\n";

    vector<int> ans(n, 0);
    for (int i = 0; i < n; ++i) {
        // vector<int> inv(m);
        // for (int j = 0; j < m; ++j) {
        //     inv[a[i][j]] = j;
        // }
        // print_container(a[i], "inverse of a=", "");
        // print_container(inv, " is inv=");

        // auto it = lower_bound(sorted.begin(), sorted.end(), inv);
        // if (it != sorted.end()) ans[i] = max(ans[i], longest_common_prefix(inv, *it));
        // if (it != sorted.begin()) ans[i] = max(ans[i], longest_common_prefix(inv, *(it - 1)));

        auto it = lower_bound(sorted.begin(), sorted.end(), a[i]);
        if (it != sorted.end()) ans[i] = max(ans[i], longest_common_prefix(a[i], *it));
        if (it != sorted.begin()) ans[i] = max(ans[i], longest_common_prefix(a[i], *(it - 1)));
    }

    for (int num : ans) cout << num << " ";
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
