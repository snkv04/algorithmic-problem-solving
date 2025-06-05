#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

template <typename Container>
void print_container(const Container &c, string prefix = "", std::ostream &os = std::cout) {
    os << prefix << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]" << endl;
}

void solve() {
    /*
    some key observations:
    a rectangle operation of any size can be substituted (although many operations might be needed)
        by operations of the minimum, 2x2, size.
    regardless of what operation takes place, the column sums and the row sums stay the same, always.

    break the solution down in a way that allows even my dumbass to intuitively understand it:
    basically, first observe based on the description of the operations in the problem that the column
    sums and row sums will remain invariant. if this condition isn't met among all the rows/columns
    between the matrices a and b, then it's obviously impossible to make the transformation. now, to
    see that only checking that condition is enough, we can make the observation written above: an
    operation of any size has a set of 2x2 operations that can replace it and have an equivalent
    effect. this means that, using a greedy algorithm, we can iterate through the rows and columns
    (i.e., through each cell in row-major order), and finalize the corresponding cell with a single
    operation. this means that the only cells which aren't guaranteed to be able to become equal to
    the cells in b are the ones on the bottom row and right column, but if we already know that the
    row sums in a are equal to the row sums in b (and same for the columns) and also that all cells
    in a row (or column) are guaranteed to be able to be made equal (without changing any sums),
    then the first of those two pieces of information means that we can also make the last cell in
    any row (or column) equal. therefore, knowing that the row and column sums are equal across
    the matrices a and b is sufficient to be able to say that a can be made into b using the given
    operations.
    now, there are two solutions here. one is to actually go and perform the greedy algorithm,
    setting each cell in a to the target value found in b, and then finally checking if the bottom
    row and right column also are equal to those in b. the other solution is to simply check the
    row and column sums as described above.

    what are some concepts in here that can be more generalized by removing some subset of
    problem-specific parameters, and then if the core idea is used in varying forms in other
    problems, then it can be considered a pattern?
    when considering imposing an operation on some state, see if it can be swapped out for a group
        of smaller (or maybe larger) operations
    when an operation is placed on some single area of the input, consider the categories that that
        area falls into (like a cell might be part of a single row, a column, a specific diagonal,
        either the set of cells whose rowidx+colidx is odd or even, etc.) and see if some properties
        of that category (like the sum across cells, the parity, the primality, the gcd with some
        other number, etc.) stays invariant or changes in some predictable, patterned way. in other
        words, when an operation is applied, look at properties in the bigger picture of where the
        operation is applied
    see if necessary conditions could also be sufficient. in this problem, the condition is necessary
        (because it must always be true whenever we apply an operation so if we want to get from
        point a to point b using only those operations then that condition must hold), but if we also
        consider the observation that we can ALWAYS make the cells except the bottom row and rightmost
        column (doesn't even have to be those sides, just some two perpendicular sides, due to the fact
        that the minimum operation size is 2x2) into the same as the corresponding cells from b, then
        we can find out that the if the condition is true, then it guarantees that we can find a
        solution since it means that the remaining cells can also definitively be made into their
        target values.
    */

    // // first solution
    // int n, m;
    // cin >> n >> m;
    // int a[n][m], b[n][m];
    // for (int i = 0; i < 2 * n; ++i) {
    //     string s;
    //     cin >> s;
    //     for (int j = 0; j < m; ++j) {
    //         if (i < n) {
    //             a[i][j] = s[j] - '0';
    //         } else {
    //             b[i-n][j] = s[j] - '0';
    //         }
    //     }
    // }

    // bool works = true;
    // for (int i = 0; i < n-1 && works; ++i) {
    //     for (int j = 0; j < m-1; ++j) {
    //         if ((a[i][j] + 1) % 3 == b[i][j]) {
    //             a[i][j] = (a[i][j] + 1) % 3;
    //             a[i+1][j+1] = (a[i+1][j+1] + 1) % 3;
    //             a[i+1][j] = (a[i+1][j] + 2) % 3;
    //             a[i][j+1] = (a[i][j+1] + 2) % 3;
    //         } else if ((a[i][j] + 2) % 3 == b[i][j]) {
    //             a[i][j] = (a[i][j] + 2) % 3;
    //             a[i+1][j+1] = (a[i+1][j+1] + 2) % 3;
    //             a[i+1][j] = (a[i+1][j] + 1) % 3;
    //             a[i][j+1] = (a[i][j+1] + 1) % 3;
    //         }

    //         if ((i+1 == n-1 && a[i+1][j] != b[i+1][j])
    //                 || (j+1 == m-1 && a[i][j+1] != b[i][j+1])
    //                 || (i+1==n-1 && j+1==m-1 && a[i+1][j+1] != b[i+1][j+1])) {
    //             works = false;
    //             break;
    //         }
    //     }
    // }
    // cout << (works ? "YES" : "NO") << "\n";

    // second solution
    int n, m;
    cin >> n >> m;
    int a[n][m], b[n][m];
    for (int i = 0; i < 2 * n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < m; ++j) {
            if (i < n) {
                a[i][j] = s[j] - '0';
            } else {
                b[i-n][j] = s[j] - '0';
            }
        }
    }

    vector<int> ra(n, 0), rb(n, 0), ca(m, 0), cb(m, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ra[i] = (ra[i] + a[i][j]) % 3;
            rb[i] = (rb[i] + b[i][j]) % 3;
            ca[j] = (ca[j] + a[i][j]) % 3;
            cb[j] = (cb[j] + b[i][j]) % 3;
        }
    }
    
    bool works = true;
    for (int i = 0; i < max(n, m) && works; ++i) {
        if (i < n && ra[i] != rb[i]) works = false;
        if (i < m && ca[i] != cb[i]) works = false;
    }
    cout << (works ? "YES" : "NO") << "\n";
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
