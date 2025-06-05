#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    /**
     * from the problem, we know that any competitor can solve any problem with a difficulty at most
     * that competitor's rating, and so any problem can be solved by a competitor with a rating at
     * least that problem's difficulty. if all the problems in a given contest are of a difficulty
     * less than or equal to kevin's rating, then all of the competitors with a rating higher than
     * kevin will be "grouped up" into the same rank, rank 1. note that if kevin gets a rank like 5,
     * then whether the rank 2 and 3 people got the same number of problems (in which they'd be tied
     * at rank 2) or different numbers of problems does not matter; so, this means that we just care
     * about maximizing the number of competitors at kevin's rating and higher to some extent that
     * all get grouped up into the same rank, because those that get higher ranks (which is possibly
     * none at all) were able to solve strictly more problems. we could look at how many problems
     * each competitor is able to solve, but that could get messy because the actual problems in each
     * contest change. so, let's instead look at how many competitors can solve each problem.
     * if we calculate this and then sort them, then we can find a simple way to group up the problems
     * into the individual contests. in order to maximize the number stated earlier (the number of
     * competitors with rating at least that of kevin's who all get the same rank), we can group up
     * the problems starting from those which can be solved by the least people; this greedy strategy
     * is justified by the fact that any other grouping would cause there to be larger maximum values
     * than otherwise. the one caveat is that we shoulds start with all the problems whose difficulties
     * are lower than kevin's rating, as putting all of those in one problem set would give kevin and
     * all of the higher-rated people a rank 1. to do this, we can just treat all of those as having
     * 0 people able to solve them. through this, it can be seen that if those mix in with the first
     * of the remaining problems (that can actually be solved by 0, 1, 2, etc. people) then there is
     * no issue.
     */

    int n, m;
    cin >> n >> m;
    int a[n], b[m];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int kevin = a[0];
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    sort(a, a+n); sort(b, b+m);

    // just getting the worst rank he can obtain
    int l = 0, r = n-1, maxrank = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a[mid] <= kevin) {
            maxrank = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    maxrank = n - maxrank;
    
    int cansolve = 0;
    for (int i = m-1; i >= 0; --i) {
        while (n-cansolve-1 >= 0 && a[n-cansolve-1] >= b[i]) {
            ++cansolve;
        }

        b[i] = cansolve >= maxrank ? 0 : cansolve;
    }
    sort(b, b+m);
    // cout << "counts: "; for (int i = 0; i < m; ++i) cout << b[i] << " "; cout << "\n";

    for (int k = 1; k <= m; ++k) {
        ll ans = 0;
        for (int j = k-1; j < m; j += k) {
            ans += b[j] + 1;
        }
        cout << ans << " ";
    }
    cout << "\n";
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
