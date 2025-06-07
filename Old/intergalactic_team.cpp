#include <iostream>
#include <vector> 
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;


const int MAXN = 1e5 + 10;
const int inf = 1e9;
#define fi first
#define se second 
#define ll long long

int n,m,k;
map<int,int> ma[MAXN];
vector<int> v[MAXN];
vector<int> num;
int vis[MAXN];

pair<ll,ll> dfs(int x) {
    vis[x] = 1;
    pair<ll,ll> ans;
    ans.fi = 1;
    ans.se = v[x].size();

    for (int i = 0;i < v[x].size();i++) {
        int y = v[x][i];
        if (vis[y] == 1) continue;
        pair<ll,ll> cur = dfs(y);
        ans.fi += cur.fi;
        ans.se += cur.se;
    }

    return ans;
}


void solve() {
    cin >> n >> m >> k;
    for (int i = 1;i <= m;i++) {
        int x,y;
        cin >> x >> y;
        if (x > y) swap(x,y);
        ma[x][y]++;
        if(ma[x][y] == 2) {
            v[x].push_back(y);
            v[y].push_back(x);
        }
    }

    if (k==1) {
        int ans = 0;
        for (int i = 1;i <= n;i++) if (v[i].size() == 0) ans++;
        cout << ans;
        return;
    }
    
    int cnt = 0;
    for (int i = 1;i <= n;i++) if(vis[i] == 0) {
        pair<ll,ll> cur = dfs(i);
        if (cur.fi != k) continue;
        if (cur.fi * (cur.fi - 1)  == cur.se) cnt++;
    }

    cout << cnt;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}