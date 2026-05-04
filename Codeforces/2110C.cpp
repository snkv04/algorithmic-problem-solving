

#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n;
  cin >> n;
  vector<int> d(n);
  for (int i = 0; i < n; ++i) cin >> d[i];
  vector<int> l(n), r(n);
  for (int i = 0; i < n; ++i) {
    cin >> l[i] >> r[i];
  }

  int wl = 0, wr = 0;
  queue<int> q;  // stack or queue, doesn't matter where we get the "-1"s to overwrite from (left or right)
  for (int i = 0; i < n; ++i) {
    if (d[i] == 1) { wl += 1; wr += 1; }
    else if (d[i] == -1) { q.push(i); wr += 1; }

    if (wl > r[i] || wr < l[i]) { cout << "-1\n"; return; }

    int offtop = max(0, wr - r[i]);
    int offbottom = max(0, l[i] - wl);
    if (offtop + offbottom > q.size()) { cout << "-1\n"; return; }
    while (offtop--) {
      d[q.front()] = 0;
      q.pop();
    }
    while (offbottom--) {
      d[q.front()] = 1;
      q.pop();
    }
    wr = min(wr, r[i]);
    wl = max(wl, l[i]);
  }

  for (int i = 0; i < n; ++i) if (d[i] == -1) d[i] = 0;
  for (int i = 0; i < n; ++i) cout << d[i] << " ";
  cout << "\n";
}

int main() {
  int t;
  cin >> t;
  while ((t -= 1) >= 0) {
    solve();
  }

  return 0;
}
