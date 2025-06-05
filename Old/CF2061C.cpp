#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    /*
    if you go from the left to the right, assigning T or L to each person, then at any
    given current index, you know exactly what the correct number of liars to the left
    is, so you can determine if someone is definitely a liar or if they can be either.
    so, one way to view this is to start from the left and traverse down a tree being built,
    where left branches correspond to a truth teller and right branches correspond to the
    current element being a liar. obviously, many branches will be pruned out. but, another
    way to view this is to imagine the same tree but with the right of the array at the root
    and the left of the array at the leaf level. given this, it's easier to see that this
    is DP, since a common form of DP is skipping over the recomputation of subtrees in a
    decision tree, and any index from the left represents a subtree. now, we just use DP
    to represent the number of possible assignments for the subarray whose right bound is
    the current element, assuming that the current element is either a T or an L (which
    makes for an easy representation when transitioning from previous states to the current
    one). the formulas for computing the values come straight from the rules in the problem.
    also, a 0 is prepended to the array, to allow for at least 1 assignment to exist and
    since that can either be a T or an L.

    what really makes this problem confusing at all?
    it's kind of just the unique rules of each element representing the number of liars to
    the left, which has interesting dynamics with the truth-telling status of the person saying
    that number, and how two liars can't be in adjacent positions. however, one way to simplify
    this problem is to view it as a straightforward assignment problem with some constraints.
    basically, without any of the rules imposed, the answer is straightforwardly 2^n, but because
    of them, not all of the assignments are valid. so, just move from left to right, imposing
    those rules to calculate the actual number. most of the information that we can rely upon
    comes from the truthful elements.

    why is the prepended element a 0?
    the obvious reason is that it's the only truthful value, so setting it as that allows this
    nonexistent (in the input) preliminary element to either be T or L. it also just aligns with
    what we want from the first actual element in the input in the 4 cases for the assignments
    to (0, 1): LL (not possible, so 0 ways), TL (easily possible for first elem in input to be
    a lie, so 1 way), TT (only works if elem 1 is 0, and since elem 0 is 0, it lines up and creates
    1 way), and LT (this is only possible if elem 1 is 1, which doesn't make sense in context since
    there can't be 1 liar to the left of the first elem in the input, so 0 ways).
    */

    int n;
    cin >> n;
    vector<int> a;
    a.push_back(0);
    for (int i = 1; i <= n; ++i) {
        int ai;
        cin >> ai;
        a.push_back(ai);
    }

    ll mem[n+1][2];
    for (int i = 0; i <= n; ++i) fill(mem[i], mem[i]+2, 0);
    mem[0][0] = 1; mem[0][1] = 1;
    for (int i = 1; i <= n; ++i) {
        mem[i][1] += mem[i-1][0];
        mem[i][1] %= MOD;

        if (a[i] == a[i-1]) {
            mem[i][0] += mem[i-1][0];
        }
        if (i >= 2 && a[i] == a[i-2] + 1) {
            mem[i][0] += mem[i-2][0];
        }
        mem[i][0] %= MOD;
    }
    cout << ((mem[n][0] + mem[n][1]) % MOD) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
