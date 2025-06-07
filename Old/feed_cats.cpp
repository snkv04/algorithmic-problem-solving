#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

struct Cmp1 {
    bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) const {
        return p1.first < p2.first;
    }
};

struct Cmp2 {
    bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) const {
        return p1.second >= p2.second;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> segments(m, pair<int, int>());
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        // segments.push_back(pair<int, int>(l, r));
        segments[i].first = l;
        segments[i].second = r;
    }
    sort(segments.begin(), segments.end(), [](const auto &p1, const auto &p2) {
        return p1.first < p2.first;
    });
    // cout << "segments:\n";
    // for (const auto &segment : segments) {
    //     cout << "(" << segment.first << ", " << segment.second << ")\n";
    // }

    int mem[n+1];
    fill(mem, mem+n+1, 0);
    int j = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp2> rights;
    multiset<pair<int, int>, Cmp1> lefts;
    for (int i = 1; i <= n; ++i) {
        while (j < m && segments[j].first == i) {
            pair<int, int> p = segments[j++];
            lefts.insert(p);
            rights.push(p);
            // cout << "i=" << i << ", pushing (" << p.first << ", " << p.second << ")\n";
        }

        while (rights.size() && rights.top().second < i) {
            auto p = rights.top();
            rights.pop();
            lefts.erase(lefts.find(p));
            // cout << "i=" << i << ", popping (" << p.first << ", " << p.second << ")\n";
        }

        cout << "i = " << i << "\n";
        auto copy = priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp2>(rights);
        cout << "rights = ";
        while (copy.size()) {
            pair<int, int> top = copy.top();
            copy.pop();
            cout << "(" << top.first << ", " << top.second << ") ";
        }
        cout << "\n";

        cout << "lefts = ";
        for (auto &p : lefts) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << "\n";

        mem[i] = mem[i-1];
        if (lefts.size()) {
            mem[i] = max(mem[i], mem[(*lefts.begin()).first - 1] + (int) rights.size());
        }
    }
    // cout << "mem = \n";
    // for (int i = 0; i <= n; ++i) cout << mem[i] << " ";
    // cout << "\n";
    cout << mem[n] << "\n";
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
