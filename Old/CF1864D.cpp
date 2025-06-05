#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

int downleft(int i, int j) {
    return i + j;
}

int downright(int i, int j, int n) {
    return i - j + (n-1);
}

void solve() {
    // if we have a bunch of intervals each defined as (l, r) across some range, then
    // constructing an array to represent how many intervals cover a specific index
    // can be easily done through the well-known strategy of making an array with +1
    // directly on each l value and -1 right after each r value, and then just constructing
    // the prefix sum array of that array.
    // in this problem, first we can notice that no operation impacts any row above it. this
    // means that if there is an issue (where we define an issue to be any cell that, with
    // all operations having been applied to it, is equal to 1), then we should deal with it
    // before moving to future rows. this gives us a general strategy: move from row to row
    // starting with the top row, iterate through the cells, and for each check if we need
    // to apply an operation with that cell at the top. cells in the same row don't impact
    // each other with regard to the collateral of operations applied to them, so we don't
    // need to consider any more operations than this. to show that it's the least number
    // of operations needed, note that after having applied all operations from previous
    // rows, each column in the current row must be changed if it's a 1; it cannot be avoided,
    // so, in other words, we can't do with less operations than this.
    // how exactly can we keep track of the operations performed here? well, there are
    // multiple ways, but the key idea is that we use separate arrays to keep track of
    // the starts and ends of the operations. if we were to immediately apply all operations
    // into some prefix sum array in one row, then for the next row, we wouldn't know where
    // the starts and ends were of the operations from all previous rows, so we wouldn't be
    // able to "expand" the operation by one unit to the left and one unit to the right
    // (in that pyramid shape). instead, we keep track of the lefts and rights of all operations
    // from previous rows separately, and at the beginning of each row, we get an array which
    // says, for each column j, how many operations from prev rows have been applied to the
    // cell at (current row, j). to keep track of these, either we can literally keep track
    // of the left and right in terms of columns, and move the lefts to the left and the rights
    // to the right at each row before constructing the prefix sums to actually "apply" the
    // operations, or store the lefts and rights corresponding to diagonal indices. with
    // this method, the lefts are stored on the downleft diagonal, the rights are stored on
    // the downright diagonal, and the array of applied operations for each (row, col) = (i, j)
    // at any given row i is constructed by walking through each of those arrays using the
    // corresponding diagonal index as we walk through j. the actual internals of how we
    // store the interval start and end counts in diagonal indices doesn't matter; for example,
    // for the downright diagonal, moving to the down and left increases the index and moving
    // to the up and right decreases the index, but reversing this wouldn't really matter as
    // long as two cells on the same diagonal have the same index, since the downleft information
    // and the downright information are stored independently.

    int n;
    cin >> n;
    string grid[n];
    for (int i = 0; i < n; ++i) cin >> grid[i];

    vector<int> on(2*n-1, 0), off(2*n-1, 0);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        vector<int> appliedfrompast(n, 0);
        int acc = 0;
        for (int j = -i; j < 0; ++j) {
            acc += on[downleft(i, j)];
        }

        for (int j = 0; j < n; ++j) {
            acc += on[downleft(i, j)];
            acc += off[downright(i, j, n)];
            appliedfrompast[j] = acc;
        }

        vector<int> onforfuture = on, offforfuture = off;
        for (int j = 0; j < n; ++j) {
            int cell = grid[i][j] - '0';
            cell += appliedfrompast[j];
            if (cell % 2) {
                ++ans;
                onforfuture[downleft(i, j)] += 1;
                int off_idx = downright(i, j+1, n);
                if (off_idx >= 0) {
                    offforfuture[off_idx] -= 1;
                }
            }
        }
        on = onforfuture;
        off = offforfuture;
    }
    cout << ans << "\n";
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
