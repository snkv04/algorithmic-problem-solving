// not my code; don't want to take credit for it

// Even Ford-Fukerson works: O(N^2 + N*R) for this particular problem since
// maxflow <= N and the graph has size O(N + R).

#include <bits/stdc++.h>

const int INF = 1e9; // set >= max capacity

using namespace std;

vector<unordered_map<int, int>> g;
vector<int> par;

void init(int n) { g = vector<unordered_map<int, int>>(n); }
void add_edge(int u, int v, int c) { g[u][v] = c; }

int augment(int v, int pre, int t, int mn) {
  if (v == t) return mn;
  if (par[v] != -1) return 0;
  par[v] = pre;

  for (auto& p : g[v]) {
    if (p.second == 0) continue;
    int nxt = augment(p.first, v, t, min(mn, p.second));
    if (nxt) {
      p.second -= nxt;
      g[p.first][v] += nxt;
      return nxt;
    }
  }
  return 0;
}

// augment until done, the mincut is stored in par, no need to know flow value
void mincut(int s, int t) {
  do { par.assign(g.size(), -1);
  } while(augment(s, -2, t, INF));
}

int main() {
  int N, R;
  cin >> N >> R;

  string team, change;
  cin >> team >> change;

  init(2*N+2);

  auto in = [](int i) { return 2*i; };
  auto out = [](int i) { return 2*i+1; };
  int s = 2*N, t = 2*N+1;

  for (int i = 0; i < N; ++i) {
    if (change[i] != '?') {
      if (team[i] == change[i]) add_edge(s, in(i), INF); // flow can be inf
      else add_edge(out(i), t, INF); // flow can be inf
    }
    add_edge(in(i), out(i), 3);
  }

  while (R--) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    // bool ustaysame = change[u] != '?' && team[u] == change[u];
    // bool vstaysame = change[v] != '?' && team[v] == change[v];
    // if ((ustaysame && vstaysame) || (!ustaysame && !vstaysame)) continue;
    add_edge(out(u), in(v), INF);
    add_edge(out(v), in(u), INF);
  }

  mincut(s, t);

  string final(N, '_');
  for (int i = 0; i < N; ++i)
    if (par[in(i)] != -1 && par[out(i)] == -1) { // this vertex was cut
      final[i] = 'X';
    } else {
      if (par[in(i)] != -1) {
        // this vertex is in S, meaning that it's visitable from s
        final[i] = team[i];
      } else {
        // this vertex is in T, meaning that it's not visitable from t
        final[i] = (team[i] == 'A' ? 'B' : 'A');
      }
    }
  cout << final << endl;

  return 0;
}
