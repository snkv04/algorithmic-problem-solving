#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    /*
    we want to find (at most 300,000 times), given a fixed vertex a and b, what the
    minimum possible k'th largest edge weight is on a path between a and b. we can
    reframe this problem as follows: given the ends of the path a and b, what is the
    minimum possible edge weight such that the edges on a path between a and b include
    that edge and also that all of the heaviest k of these edges (from that same path)
    are greater than or equal to that edge weight? to do this, we can do binary search,
    but that binary search algorithm requires computing some prerequisite information.
    first off, given the path's ends a and b, 

    in what way can this problem being reframed to binary search be generalized to
    other types of problems?

    why are we sorting from shortest to longest edges instead of the other way around?

    what similarities does this algorithm have to floyd-warshall?

    how could i come to this solution on my own?
    */

    int n, m, q;
    cin >> n >> m >> q;
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
