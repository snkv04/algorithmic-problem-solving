#include <bits/stdc++.h>
using namespace std;

template <typename T, size_t N>
std::ostream& operator<<(std::ostream &os, const array<T, N> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const vector<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

void solve() {
    /*
    - same idea as https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/, but instead
    of adding in the single rightmost tree for each interval (if the interval hasn't already been covered),
    we add in the remaining required number of rightmost trees in each interval (where i say "remaining" as
    some might have already been added in the interval due to previously-processed intervals)
    */

    int n, k;
    cin >> n >> k;
    vector<int> x(n); for (int i = 0; i < n; ++i) cin >> x[i];
    sort(x.begin(), x.end());
    // cout << "x = " << x << endl;
    vector<array<int, 3>> intervals(k);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> intervals[i][j];
        }
    }
    sort(intervals.begin(), intervals.end(), [](const array<int, 3> &first, const array<int, 3> &second) {
        return first[1] < second[1]; // sort by right endpoint
    });
    // cout << "intervals = " << intervals << endl;

    int ans = n;
    vector<bool> used(n, false);
    for (auto interval : intervals) {
        int l = interval[0], r = interval[1], t = interval[2];
        int req = t;
        for (int i = 0; i < n; ++i) {
            if (x[i] >= l && x[i] <= r && used[i]) --req;
        }
        if (req <= 0) continue;

        ans -= req;
        for (int i = n-1; i >= 0 && req; --i) {
            if (!used[i] && x[i] <= r) {
                --req;
                used[i] = true;
            }
        }
    }
    cout << ans << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
