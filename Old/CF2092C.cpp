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
    observations:
    we can operate on any two towers of different parity
    evens can be concatenated to odds without switching parity
    odds can be concatenated to evens but this makes them odd

    if all are of the same parity, then obviously we can't do any operations. otherwise,
    we move all evens onto odd numbers, and then we're left with all odd numbers. now,
    for each of the odds except one (which will act as the accumulator), use the empty
    spaces of value 0 from the evens (which there's at least one of) to move a single 1
    into, and since the number is now even, concatenate it into the odd accumulator.

    generalizable idea, which could be a pattern if it's seen in other problems:
    perform the simple, easy operations first (which, in this case, is moving all of the
    even numbers onto an odd, since those even numbers don't change an odd's parity),
    and then try to find how to go from that state to the solution (which, in this case,
    refers to using those empty spaces to allow each of the other odds to be eligible
    for an operation between itself and the accumulator which is odd)

    what's an alternate idea, and why wouldn't that work or at least be less simple
    than this solution?
    specify an accumulator, then individually try to make each element add to it, where
    if it's odd then we move a 1 to another element and then add it to the accumulator.
    this impacts future elements that we look at (both in their value and their parity),
    and finding those future elements to make the transfer might be costly, whereas with
    the first solution, the first step is very quick and easy, and the second step is also
    straightforward once we arrive at the problem state (all odd numbers and some nonempty
    set of 0s) that the first step causes the initial state to transform into.
    */

    int n;
    cin >> n;
    int a[n];
    ll even = 0, odd = 0, sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] % 2) {
            ++odd;
        } else {
            ++even;
        }
        sum += a[i];
    }

    if (!even || !odd) {
        int mx = 0;
        for (int ai : a) mx = max(mx, ai);
        cout << mx << "\n";
    } else {
        cout << (sum - odd + 1) << "\n";
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
