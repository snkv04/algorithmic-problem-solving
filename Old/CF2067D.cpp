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

void solve() {
    /*
    it's clear that a query result of 0 can only happen with object A, so if we get that,
    then we know that it's object A. no matter what query we do, we'll never get 0 if we
    have object B. how can we exploit that? well, in what cases would there not be a path?
    nodes that are the destination of no edges would obviously be unreachable, but in actuality,
    it's also true that nodes which have no outgoing edges (are the source of no edges)
    cannot reach anything. the "unreachability" is applied at the start of the path conceptually.
    in other words, instead of relying on the set of information that we don't know (the y values),
    we can rely on the information we do know (the x vector), and see how we can identify an edge
    that is definitely not in the graph. this can simply be done by noticing any number from 1 to
    n that is not in the x vector, and seeing if a query of (that number, any number) results in
    0 or a positive number.
    now, that actually solves many cases, and can be used in those cases, but the ONLY cases in
    which this won't work are when x is a permutation of the integers from 1 to n. in the case of
    object B, this means that there is a point with every x value from 1 to n. the key observations
    here are that queries of (i, j) and (j, i) would be equal for object B but not NECESSARILY for
    object A, that the Manhattan distance between nodes with x-values of 1 and n are at LEAST n-1
    (because the y distances is nonnegative), and that even in the case of an even-length cycle in
    a graph, where the distances in the n-length cycle between two nodes in both directions could
    be equal if they're both n/2, they will never BOTH be as large as n-1. one of them might be,
    but the total distance of the cycle is constrained by n, so they can't both be.
    */

    int n;
    cin >> n;
    set<int> unused; for (int i = 1; i <= n; ++i) unused.insert(i);
    int idx1 = -1, idxn = -1;

    for (int i = 0; i < n; ++i) {
        int xi;
        cin >> xi;
        unused.erase(xi);
        if (xi == 1) {
            idx1 = i + 1;
        }
        if (xi == n) {
            idxn = i + 1;
        }
    }

    if (unused.size()) {
        cout << "? " << *unused.begin() << " " << (*unused.begin() == 1 ? 2 : 1) << endl;
        int result;
        cin >> result;
        if (result == 0) {
            cout << "! A" << endl;
        } else {
            cout << "! B" << endl;
        }
    } else {
        cout << "? " << idx1 << " " << idxn << endl;
        int result1, result2;
        cin >> result1;
        cout << "? " << idxn << " " << idx1 << endl;
        cin >> result2;
        if (result1 == result2 && result1 >= n-1) {
            cout << "! B" << endl;
        } else {
            cout << "! A" << endl;   
        }
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
