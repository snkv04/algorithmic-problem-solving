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
    notes:
    - when undoing operations, we can place lower bounds on what the input values
    were; that much is pretty clear. however, there are other restrictions that
    can be placed, such as: two values are both greater than or equal to 3, but
    one of them must have been equal to 3, because the output of the min operation
    was 3. basically, what the solution is doing here is ignoring such restrictions
    and assuming that only the min restrictions apply, so that the full state
    at the current step is valid, and then everything is checked at the end. another
    example is if x, y, and z are all distinct, and we end up with an operation
    which tells us that the min of 3 and 5 was equal to 2; in this case, we'd just
    gleefully assume (for each of 3 and 5) that the other element was responsible
    for the minimum and update 3 to be max(3, 2) (as well as updating 5 to be
    max(5, 2)), and then check our assumptions at the end.

    generalizable ideas?
    - basically, there are two ways to solve this problem (with the first one
    being much more complex and, possibly, computationally infeasible). we know
    that what we're trying to do is see if an end state is possible, and if it is,
    then we want to give a possible start state for that end state. both ways involve
    going backward from the end state. the first is to keep track of all current
    and past restraints, and as soon as any of them are "broken" (meaning that
    we are now forcing the array to be in a situation that is not consistent with
    a past constraint), then we know that the sequence of operations is impossible,
    otherwise we go all the way and output the array after undoing all the ops.
    the second is to assume at EACH OPERATION that the output of the operation
    is possible and to force the inputs to make that output possible, not worrying
    about if it's actually possible or about past (or future, since we're going
    backwards) operations, and then go through all the operations again and see
    if the final output is what it's supposed to be. the second is more easily
    implementable, and is also correct. (why, specifically?)
    - more generally, perhaps, instead of going through all operations and checking
    the conditions placed by the current and past ones, we just go through the
    operations only worrying about the current, then do a final pass through all
    to make sure that the whole sequence of operations is still valid.
    */

    int n, q;
    cin >> n >> q;
    vector<int> b(n); for (int i = 0; i < n; ++i) cin >> b[i];
    int queries[q][3];
    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < 3; ++j) {
            cin >> queries[i][j];
            queries[i][j]--;
        }
    }

    vector<int> c = b;
    for (int i = q-1; i >= 0; --i) {
        int x=queries[i][0], y=queries[i][1], z=queries[i][2];
        int output = c[z];
        c[z] = 0;
        c[x] = max(c[x], output);
        c[y] = max(c[y], output);
    }

    vector<int> a = c;
    for (int i = 0; i < q; ++i) {
        int x=queries[i][0], y=queries[i][1], z=queries[i][2];
        c[z] = min(c[x], c[y]); 
    }

    bool works = true;
    for (int i = 0; i < n; ++i) {
        if (c[i] != b[i]) {
            works = false;
            break;
        }
    }
    if (works) {
        for (int i = 0; i < n; ++i) cout << a[i] << " ";
        cout << "\n";
    } else {
        cout << "-1\n";
    }
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
