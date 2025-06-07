#include <iostream>
#include <stack>
 
using namespace std;
 
const int MAXN = 100005;
int a[MAXN];
bool visited[MAXN];
bool in_cycle[MAXN];
stack<int> reverse_toposort;
bool on_stack[MAXN];
 
void dfs(int node) {
    visited[node] = true;
    on_stack[node] = true;
    if (!visited[a[node]]) {
        dfs(a[node]);
    } else if (on_stack[a[node]]) {
        in_cycle[node] = true;
    }
    on_stack[node] = false;
    reverse_toposort.push(node);
}
 
void solve() {
    int n;
    cin >> n;
    fill(a, a+n, -1);
    fill(visited, visited+n, false);
    fill(in_cycle, in_cycle+n, false);
    for (int i = 0; i < n; ++i) {
        int ai;
        cin >> ai;
        a[i] = ai-1;
    }
    int c[n];
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
 
    fill(on_stack, on_stack+n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    
    fill(visited, visited+n, false);
    int start[n];
    fill(start, start+n, -1);
    for (int i = 0; i < n; ++i) {
        if (in_cycle[i] && !visited[i]) {
            int curr = i;
            int smallest = i;
            while (true) {
                if (c[curr] < c[smallest]) {
                    smallest = curr;
                }
                curr = a[curr];
                if (curr == i) break;
            }
 
            int start_at = -1;
            curr = i;
            while (true) {
                if (start_at == -2) {
                    start_at = curr;
                    break;
                }
 
                if (curr == smallest) {
                    start_at = -2;
                }
                curr = a[curr];
            }
 
            int node = i;
            while (true) {
                in_cycle[node] = true;
                visited[node] = true;
                start[node] = start_at;
                node = a[node];
                if (node == i) break;
            }
        }
    }
 
    fill(visited, visited+n, false);
    while (!reverse_toposort.empty()) {
        int node = reverse_toposort.top();
        reverse_toposort.pop();
        if (!in_cycle[node]) {
            cout << node+1 << " ";
            visited[node] = true;
        } else {
            if (!visited[node]) {
                int curr = start[node];
                while (true) {
                    cout << curr+1 << " ";
                    visited[curr] = true;
                    curr = a[curr];
                    if (curr == start[node]) break;
                }
            }
        }
    }
    
    cout << '\n';
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
 
    return 0;
}
