#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

const int MAXN = 200005;
bool visited[MAXN], onstack[MAXN];
int first, ans;
vector<int> a;

void dfs(int node) {
    visited[node] = true;
    onstack[node] = true;
    if (!visited[a[node]]) {
        dfs(a[node]);
    } else if (onstack[a[node]]) {
        if (first == -1) {
            ++ans;
            a[node] = node;
            first = node;
        } else if (a[node] != first) {
            ++ans;
            a[node] = first;
        }
    }
    onstack[node] = false;
}

void solve() {
    /*
    if we treat this as a directed graph, then since this is a functional graph,
    we have a bunch of cycles, and a bunch of paths that lead to those cycles.
    what we want is a single cycle of length 1 and all other nodes to lead to
    that cycle, and it doesn't matter if the paths to those cycles merge randomly
    as it just has to resemble a tree structure and not a chain. therefore, we
    can pick one cycle of length 1 and make all other cycles of any length redirect
    to that one. if there are no cycles of length 1, there is at least guaranteed
    to be a cycle, so we can make that into a cycle of length 1 and then proceed
    to do the same thing.
    */

    int n;
    cin >> n;
    a = vector<int>(n, -1);
    first = -1;
    for (int i = 0; i < n; ++i) {
        int ai; cin >> ai; --ai;
        a[i] = ai;
        if (ai == i) {
            if (first == -1) {
                first = i;
            } else {
                ++ans;
                a[i] = first;
            }
        }
    }

    int indeg[n]; fill(indeg, indeg+n, 0);
    for (int i = 0; i < n; ++i) {
        ++indeg[a[i]];
    }
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    
    cout << ans << '\n';
    for (int i = 0; i < n; ++i) {
        cout << a[i] + 1 << ' ';
    }
    cout << '\n';
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
