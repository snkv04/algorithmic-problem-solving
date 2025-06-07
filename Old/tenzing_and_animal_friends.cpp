#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Restriction {
    ll a, b, time;

    Restriction(ll a, ll b, ll time) {
        this->a = a;
        this->b = b;
        this->time = time;
    }
    
    bool operator<(const Restriction &other) const {
        return this->time >= other.time;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> adj[n];
    while (m--) {
        int a, b, limit;
        cin >> a >> b >> limit;
        --a; --b;
        adj[a].push_back(make_pair(b, limit));
        adj[b].push_back(make_pair(a, limit));
    }

    unordered_set<int> curr;
    vector<string> games;
    priority_queue<Restriction> pq;
    for (const auto &p : adj[n-1]) {
        pq.push(Restriction(n-1, p.first, p.second));
    }
    for (int i = 0; i < n-1; ++i) {
        curr.insert(i);
    }

    ll last = 0;
    ll sum = 0;
    while (pq.size()) {
        Restriction r = pq.top();
        pq.pop();
        if (curr.find(r.a) != curr.end() || curr.find(r.b) != curr.end()) {
            ll elapsed = r.time;
            ll in, other;
            if (curr.find(r.a) == curr.end()) {
                other = r.a;
                in = r.b;
            } else {
                in = r.a;
                other = r.b;
            }

            if (elapsed - last > 0) {
                stringstream ss;
                for (int i = 0; i < n; ++i) {
                    ss << (curr.find(i) != curr.end() ? 1 : 0);
                }
                ss << " " << elapsed - last;
                sum += elapsed - last;
                games.push_back(ss.str());
                last = elapsed;
            }

            curr.erase(in);
            for (const auto &p : adj[in]) {
                pq.push(Restriction(in, p.first, last + p.second));
            }
            if (in == 0) {
                break;
            }
        }
    }

    if (pq.empty() && curr.size() && curr.find(0) != curr.end()) {
        cout << "inf\n";
    } else {
        cout << sum << " " << games.size() << "\n";
        for (string &s : games) {
            cout << s << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
