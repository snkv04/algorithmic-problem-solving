#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Comp {
    bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) {
        return p1.second >= p2.second;
    }
};

bool in_bounds(int i, int j , int h, int w) {
    return i >= 0 && i < h && j >= 0 && j < w;
}

bool on_edge(int i, int j, int h, int w) {
    return i == 0 || i == h-1 || j == 0 || j == w-1;
}

void solve() {
    int k, w, h;
    cin >> k >> w >> h;
    unordered_map<char, int> mp;
    for (int i = 0; i < k; ++i) {
        char key; int val;
        cin >> key >> val;
        mp[key] = val;
    }

    int grid2[h][w];
    int si, sj;
    for (int i = 0; i < h; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < w; ++j) {
            if (mp.find(s[j]) != mp.end()) {
                grid2[i][j] = mp[s[j]];
            } else {
                grid2[i][j] = 0;
                si = i; sj = j;
            }
        }
    }
    // cout << "si = " << si << ", sj = " << sj << "\n";
    // cout << "h = " << h << ", w = " << w << "\n";

    priority_queue<pair<int, ll>, vector<pair<int, ll>>, Comp> pq;
    ll dist[h*w];
    fill(dist, dist + (h*w), (ll) 1e18);
    dist[si * w + sj] = 0;
    pq.push(pair<int, ll>(si * w + sj, 0));
    while (pq.size()) {
        pair<int, ll> p = pq.top();
        pq.pop();
        int i = p.first / w, j = p.first % w;
        if (on_edge(i, j, h, w)) {
            cout << dist[i * w + j] << "\n";
            return;
        }

        int delta[][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        for (int k = 0; k <= 3; ++k) {
            int ni = i + delta[k][0], nj = j + delta[k][1];
            if (in_bounds(ni, nj, h, w) && dist[ni * w + nj] > dist[i*w+j] + grid2[ni][nj]) {
                dist[ni * w + nj] = dist[i*w+j] + grid2[ni][nj];
                pq.push(pair<int, ll>(ni * w + nj, dist[ni * w + nj]));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // struct rlimit rl;
    // rl.rlim_cur = 64 * 1024 * 1024;
    // rl.rlim_max = 128 * 1024 * 1024;
    // if (setrlimit(RLIMIT_STACK, &rl) == -1) {
    //     perror("setrlimit failed");
    //     return 1;
    // }

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
