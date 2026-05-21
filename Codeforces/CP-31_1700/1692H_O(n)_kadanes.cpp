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
    - problem:
        - given an array, pick a subarray and an element such that the difference between (frequency of that
        element in subarray) and (frequency of anything else in subarray) is maximized
    - solution:
        - the basic idea is: we can iterate through each value in the array, transform the array so that all
        instances of it are 1 and all others are -1, and find the maximum subarray sum using Kadane's
        - to do this efficiently, for each value in the array, we ONLY iterate through its indices and infer that
        the gaps are filled with -1
    - details:
        - we don't actually have to explicitly transform the array; that's only a conceptual step of the algorithm,
        and the algorithm in code just performs the steps needed to compute the target amount
        - when indices are partitioned into groups, see if, for each group, we only have to iterate over the elements
        in that group (by "jumping" from index to index) instead of iterating over all indices
        - the only reason it's O(nlogn) and not O(n) is because using a sorted map is faster than a hashmap here :^)
        - when doing Kadane's, it's fairly easy to keep track of the left/right bounds of the optimal subarray.
        - even after simplifying the problem down from a brute-force solution, we might still have to consider the
        brute-force solution for the simplified problem (so, basically, there are multiple levels of brute-force
        solutions) before reaching the final optimal solution; so, never hesitate to consider the "slow" brute-force
        solution, because many solutions are just variations/optimizations/simplifications of the brute-force
        solution
    */

    int n;
    cin >> n;
    vector<int> x(n);
    cin >> x;
    map<int, vector<int>> indices;
    for (int i = 0; i < n; ++i) indices[x[i]].push_back(i);

    int anssum = 1, ansdie = x[0], ansl = 0, ansr = 0;
    for (auto entry : indices) {
        int curr = 1, currl = entry.second[0];
        for (int i = 1; i < entry.second.size(); ++i) {
            // find amount added since last index
            int curridx = entry.second[i], lastidx = entry.second[i-1];
            int adding = -(curridx - lastidx) + 2;

            // update curr sum
            if (curr + adding <= 1) {
                currl = curridx;
                curr = 1;
            } else {
                curr += adding;
            }

            // update best sum
            if (curr > anssum) {
                anssum = curr;
                ansdie = x[curridx];
                ansl = currl;
                ansr = curridx;
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
