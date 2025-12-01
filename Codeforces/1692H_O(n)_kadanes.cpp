#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

template <typename T>
std::istream& operator>>(std::istream &is, std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        is >> v[i];
    }
    return is;
}

void solve() {
    /*
    - the only reason it's O(nlogn) and not O(n) is because using a sorted map is faster than a hashmap here :^)

    generalizable ideas for the future:
    - this is very similar to the segment tree solution, in that we only "activate" and "deactivate" certain elements
    of the array. however, we can actually just perform Kadane's, and the reason that it's not O(n^2) is that we can
    jump from index to index to only step on the indices for each selected die value and effectively do Kadane's while
    only processing those indices.
    - when doing Kadane's, it's fairly easy to keep track of the left/right bounds of the optimal subarray.
    */

    int n;
    cin >> n;
    vector<int> x(n);
    cin >> x;
    map<int, vector<int>> indices;
    for (int i = 0; i < n; ++i) indices[x[i]].push_back(i);

    int bestsum = 1, ansdie = x[0], ansl = 0, ansr = 0;
    for (auto entry : indices) {
        int curr = 1, currL = entry.second[0];
        for (int i = 1; i < entry.second.size(); ++i) {
            int idx = entry.second[i];
            int adding = -(idx - entry.second[i-1]) + 2;
            if (curr + adding <= 1) {
                curr = 1;
                currL = idx;
            } else {
                curr += adding;
            }

            if (curr > bestsum) {
                bestsum = curr;
                ansdie = entry.first;
                ansl = currL;
                ansr = idx;
            }
        }
    }
    cout << ansdie << ' ' << ansl + 1 << ' ' << ansr + 1 << '\n';
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
