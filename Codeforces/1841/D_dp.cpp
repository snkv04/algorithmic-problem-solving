#include <bits/stdc++.h>
using namespace std;

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << "(" << p.first << ", " << p.second << ")";
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

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> segments(n);
    for (int i = 0; i < n; ++i) {
        cin >> segments[i].first >> segments[i].second;
    }
    sort(segments.begin(), segments.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        return a.second < b.second;
    });

    vector<int> mem(n+1, 0);
    for (int i = 0; i < n; ++i) {
        mem[i+1] = mem[i];
        for (int j = 0; j < i; ++j) {
            if (segments[j].second >= segments[i].first) {
                int cl = min(segments[i].first, segments[j].first);
                int cr = max(segments[i].second, segments[j].second);
                // cout << "testing out combining " << segments[j] << " with " << segments[i] << endl;

                int l = 0, r = j - 1, idx = -1;
                while (l <= r) {
                    int m = (l + r) / 2;
                    if (segments[m].second < cl) {
                        idx = m;
                        l = m + 1;
                    } else {
                        r = m - 1;
                    }
                }

                mem[i+1] = max(mem[i+1], 2 + (idx == -1 ? 0 : mem[idx+1]));
                // cout << "now, mem = " << mem << endl;
            }
        }
    }
    cout << n - mem[n] << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
