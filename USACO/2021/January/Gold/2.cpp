#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1e9;

int main() {
    /*
    - we basically have a string that implicitly encodes a graph. each character in the string can be one of
    up to 50 characters, and there exists a directed edge from index i to index j if the two characters at
    index i and j are "compatible", as defined by a 50x50 matrix. that directed edge will have a weight
    equal to the distance between the two indices. on this graph, find the shortest path from 1 to N.
    - first observation: there is absolutely no need to step on the same color twice. proof sketch: if two
    indices i and j are both of color A, and we want to get to index k with color B, then there is no need
    to ever visit both i and j; regardless of which one we visit first, it is true that both of those indices
    provide the exact same set of next indices that are available to reach, so if we visit one of them first,
    then visiting the second one will never be more optimal than simply jumping straight to k. the corollary
    of this observation: we never need to traverse more than k edges in the worst case.
    - as a result, we can try keeping track of mem[i][j], which is the shortest path to index i after having
    jumped j times, where i \in [1, n], j \in [0, k]. the shortest path to index i after j jumps is equal to
    the minimum across all indices h, where h can reach i, of mem[h][j-1] + dist(i, h).
    - for each (i, j), we can compute mem[i][j] in O(n). how to do it quicker? for a given number of jumps j,
    we can compute mem[i][j] for all i in one right and one left pass. we can either get to node i from the
    left or the right. suppose we get to it from the left. then, if we keep track of the best possible index
    to reach it from the left (after exactly j jumps), then we can compute it in O(1) time. to do this, observe
    two pieces of information: (1) the distance formula for a pair of nodes (a, b) can be separated out into a
    part that is computed when processing a, and a part that is computed when processing b, so then we don't
    need to know where we are GOING FROM a node when we process it, and (2) from a given color, we know all
    colors it can reach, and for a given color, we know all colors it can come from. with these pieces of
    information, all we need to do is: for a given number of steps j, iterate i from left to right, and
    for each i, first get the min cost after j-1 jumps across all nodes that can reach i's color (with the
    distance part already embedded into this number, so we literally just don't need to even worry about it),
    and then update the min cost across all colors that this node can reach (again, factoring in the distance
    part, so that part of it is computed now and part of it is computed when processing the "to" node).
    - here's a more linear solution (meaning each logical step ties into the next):
        - we want to get the shortest path from node 1 to node N
        - to do this, we can see that we only need K edges at most, so we can use DP and find the shortest
        path to each node after each number of edges
        - to get the shortest path to node i after j jumps, we look at all ways to get to node i after j-1
        jumps from the left and from the right. WLOG, let's suppose we only go right
        - to quickly look across all ways to get to current index i from its left side, we can do a pass
        from left to right. at each node, we (1) update the cost for all nodes that we can reach from here,
        and (2) find the minimum cost across all nodes that we can get here from
            - note: the details of WHERE we are going (and, equivalently, WHERE we came from) are handled
            through simple subtraction and addition. namely, if we hop from A to B, where A < B, then the
            cost can subtract index A while processing A and add index B when processing B. in simplest terms,
            the benefit that this provides is that at index B, we do the same exact calculation (adding B)
            regardless of what A is; we don't have to do a different calculation for the cost of each possible
            pair (A, B).
        - however, since updating all nodes we can reach from the current index is costly, we can update
        all colors instead; there's a bijection (i'm very much abusing this term) between these two sets.
            - note: intuitively, we are "grouping together" all nodes of the same color, because they share
            the same property that the set of nodes which can reach them is the same across all of them.

    questions:
    - why do we do the left-to-right pass (and opposite)? basically, by processing nodes in this order, each
    time we look at a node, we've already computed the information needed to process that node very efficiently.
    if we were to look at each node separately (such as in a left-to-right pass, or maybe a pass of a random
    order), and we couldn't use information from previously-processed nodes at any given node, then processing
    each node is O(n) for each number of jumps that we could have reached that node after.
    */

    int n, k;
    cin >> n >> k;
    vector<int> b(n); for (int i = 0; i < n; ++i) { cin >> b[i]; --b[i]; }
    vector<string> s(k); for (int i = 0; i < k; ++i) cin >> s[i];

    vector<vector<int>> mem(n, vector<int>(k+1, INF));
    mem[0][0] = 0;
    for (int j = 1; j <= k; ++j) {
        vector<int> mincost(k, INF);
        for (int i = 0; i < n; ++i) {
            if (mincost[b[i]] != INF) mem[i][j] = min(mem[i][j], mincost[b[i]] + i);

            for (int color = 0; color < k; ++color) {
                if (s[b[i]][color] == '1' && mem[i][j-1] != INF) {
                    mincost[color] = min(mincost[color], mem[i][j-1] - i);
                }
            }
        }

        mincost = vector<int>(k, INF);
        for (int i = n-1; i >= 0; --i) {
            if (mincost[b[i]] != INF) mem[i][j] = min(mem[i][j], mincost[b[i]] - i);

            for (int c = 0; c < k; ++c) {
                if (s[b[i]][c] == '1' && mem[i][j-1] != INF) {
                    mincost[c] = min(mincost[c], mem[i][j-1] + i);
                }
            }
        }
    }

    int ans = INF;
    for (int i = 0; i <= k; ++i) ans = min(ans, mem[n-1][i]);
    cout << (ans == INF ? -1 : ans) << endl;
}
