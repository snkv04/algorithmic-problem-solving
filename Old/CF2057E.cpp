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
    first off, given the path's ends a and b, there are many different paths between
    them that hold different edges. for a query, since a and b are fixed, we can binary
    search on that k'th largest edge weight (to find its minimum value), and for a
    given edge weight value being tested, we can check to see if the shortest path
    between those two nodes has k or less edges which are greater than or equal to
    the edge being tested. the question is, how can we compute the lengths of the paths
    and, in that, only consider the weights that are greater than or equal to some value?
    for this, going back to the information we need in order to do binary search, we
    can first go through all edge weights, and compute the shortest path between any
    two nodes only counting the edges greater than or equal to the current edge weight.
    a key note here: on a path between any two nodes, we can use any edges we want, but
    we are only counting the edges above (or equal to) the threshold value by assuming
    their weights are 1 and the weights of the rest are 0. we do this for all possible
    thresholds. going back to the binary search, we check to see the minimum edge
    weight threshold that gives us a total number of edges on the shortest path between
    a and b with a weight geq than the threshold that is leq k, and then output that
    threshold.

    the solution: binary search on the minimum edge weight for the query. for a given
    edge weight, suppose that all edges with greater weight have a weight of 1 and all
    edges with a lesser weight have a weight of 0, then find the shortest path between
    a and b and check if the number of edges with a greater weight on that path (i.e.,
    the length of that path by summing up the edge weights on it) is leq k to determine
    what half to do the next binary search iteration in. now, in order to compute the
    shortest path between any two vertices for a given threshold (where a threshold
    defines what edges are counted as 1 and which are 0), we can precompute these using
    an algorithm similar to Floyd-Warshall. first, we can literally use Floyd-Warshall
    to compute the shortest path for all pairs if all edges are of weight 1 (in O(n^3)),
    then we can iterate through the edge thresholds and compute the pairwise distances
    for that threshold using the previous threshold's results in O(n^2) each.

    why are we iterating in increasing edge weight order to set the edge weight values
    from 1 to 0?
    the idea is that we want to consider various edge weight values and look at what
    happens (i.e., what the shortest paths are between any two points) if we have all
    the edges with weight greater than or equal to a given threshold be "counted", or
    have their weight set to 1. so, we can iterate through the threshold values, and
    for each, the weights below will be set to 0 (since we're trying to count) and the
    weights above will be 1. as a result, if we start with 1, then we're slowly moving
    the threshold up, so we iterate through the edges in increasing weight order.

    in simple terms, describe the main transformation of the problem.
    let's just say that for a given edge weight, all edges with at least that weight
    have their new weight (maybe we could call it weight2) as 1, and the edges with
    weight below this given edge weight would have their weight2 be 0. now, what we
    care about is finding the minimum edge weight such that we can make this transformation,
    find the shortest path from a to b using these weight2 values (0 or 1 for each edge),
    and then still have the weight of that path be leq k.
    the goal here is to intuitively explain why, exactly, this is equivalent to the
    original problem.
    a brute-force solution for the original problem is to take a and b, find all possible
    paths between a and b, find the kth largest value on each of those paths, and find the
    minimum of those kth largest values. another way to phrase is is, for each of those
    possible paths, we want to find the minimum edge on that path such that there are exactly
    k edges on that same path with weight geq that minimum edge (or, as described below,
    such that for the edge right above, there are exactly k-1 edges on that same path with
    weight geq that edge right above's weight). this is directly mappable to that idea with
    setting edges to 1s and 0s and taking the sum, so that doesn't need to be elaborated
    upon. this whole solution can be said to rely on starting with applying that condition,
    namely the condition of having the number of edges on a path between two vertices that
    have weights geq a fixed weight being leq k, first, before finding what fixed edge weight
    allows for that.
    in other words, the brute-force solution looks like:
        - fix a and b
        - iterate over all paths between them
        - for each path, find the minimum edge weight s.t. there are <= k edges with geq weight
        on that path
        - find the minimum of those values across all the paths
    and this new solution looks like:
        - for each edge weight, and for each possible assignment of a and b (all pairs),
        ONLY count the edges with original weight geq that edge weight
        - select the shortest path (which can include any edges, counted or not),
        namely the includes as few edges with geq weight, and all other paths don't matter
        - precompute the number of counted edges on that path
        - now, given a and b, we can binary search to find the minimum edge weight;
        the condition of only caring about edges geq any given one is already accounted for
    quick note on why we are computing the shortest path based on the 0/1 graph
    and not the original graph:
    we want to find the min edge with <= k edges geq it on the path. if we minimize the
    edges that are geq the current edge for any given edge, then we can push the current
    edge (the one that we are finding) as low as possible. that's it.

    here, we are binary searching on the minimum edge weight, where all edges with weight
    geq that edge weight are set to 1 and all below set to 0, such that the number of edges
    with weight 1 on the path from a to b is strictly less than k, and then taking the edge
    weight right below that. the more intuitive version would be to binary search on the
    minimum edge weight such that the number of edges with weight 1 is leq k, and then just
    take that edge weight. why are we doing it the former way? probably the easiest way to
    answer this question is with an illustrative example.
    there's actually a very clear reason, which is worth remembering. i figured this out
    from analyzing the second given test case. basically, if we simply find the minimum
    possible edge weight that meets the condition, then even though IT'S TRUE that the
    actual path will have exactly k edges on it that have weight greater than or equal to
    that edge weight, it's NOT TRUE that that an edge with that weight will actually BE
    on the path. however, if we look at the minimum edge weight that has STRICTLY less
    than k edges with weight geq that edge weight, then we know the next edge down (which
    might either have the same weight or a lesser weight) will be the one that ends up
    being the kth largest edge weight. yes, there might be many more edges with the same
    weight on the path, but if they have the same weight then they can be reranked such
    that the one we care about is that kth largest one. if we think about the edges in
    terms of how many edges with weight geq that edge's weight are on the shortest path
    from a to be, then there may be many edges that result in k edges on that path. doing
    this strategy of finding the min edge weight that end up in strictly less than k edges
    on that path and then shifting over by 1 makes sure that we get the rightmost edge
    out of that set of edges. this is a key idea and is probably generalizable.
    side note: we'd have to consider the edge case of the smallest possible edge that
    meets those condition being the one with the minimum weight, so then we'd want to
    shift over by 1 but we can't. however, this will never happen, since there will
    always be at least k edges on a path between a and b (based on what the problem says),
    so then the lowest possible edge with strictly less than k edges being counted will
    at worst be the second edge (at index 1), which is completely fine.

    what similarities does this algorithm have to floyd-warshall?
    floyd-warshall iterates through all of the vertices, and updates all pairs'
    shortest path by letting those paths go to the current vertex being iterated
    over. this algorithm iterates through edges, and updates all pairs' shortest
    paths by letting those paths go through the edge, for both orientations of
    the current edge. there's not really much else to say here.

    what are some generalizable ideas from this problem?
    - we're approaching the problem from a different angle. instead of seeing the
    points a and b and trying to find the smallest weight w such that the edges
    on the path between a and b which have weight at least w are k in number,
    we fix w (in each binary search iteration) and check to see the number of edges
    with weight at least w on the shortest path between a and b and compare that
    number with k.
    - we are transforming the concept of shortest paths with edge weights into just
    setting edge weights as either 0 or 1 (simply two separate categories) and then
    computing the shortest paths. why are we doing this? for a given edge weight,
    we don't care if it's far above a threshold or just a little above threshold.
    what we are NOT doing is computing the shortest path using the original edge
    weights and then counting those (efficiently or not, this isn't being done)
    edges which are above a threshold. instead, for a given threshold, we are literally
    setting the edges above it to 1 and below it to 0, and then computing the shortest
    paths using those values. this is because, for a fixed edge weight threshold,
    the ONLY thing we care about on a path between two points is how many edges
    on that path have a weight greater than or equal to that threshold. can this
    be done any other way honestly? if it can't, then i guess this idea (of setting
    things to 0 and 1 and then summing up in order to perform counting) is a pretty
    importtant idea and this problem is just the first time that i'm seeing it.
    - we don't want to just find the minimum edge weight that meets the condition,
    because then the edge itself might not be included in the paths that we're looking
    for. we want to find the minimum edge weight that almost meets the full condition,
    so then we know that the next lower one will definitely (1) meet the condition
    (of having <= k edges on the path), and (2) will be the one that pushes the condition
    to the full extent (in this case, is the kth largest edge on the path, not any
    larger, and is actually included on that path).

    how could i come to this solution on my own?
    the brute-force (but infeasible) solution is quite obvious. the part that is
    infeasible is searching over all paths, but we can simplify it into only caring
    about one path. namely, instead of going through each path, finding the min edge
    for which some numerical property is under k, and then finding the min of that
    across all paths, we are instead directly finding the min edge, and for each edge
    THE PATH IS FIXED alongside that numerical property (if it's not already clear,
    the property is the number of edges on the path with weight geq the current edge
    being checked). we fix that path for each edge (and to do it for each pair of vertices
    requires precomputation, which can be done efficiently), and then we're basically
    doing the exact same thing in this solution: finding the minimum edge such that the
    greater edges are at most k in number. in order to carry this out, we need efficient
    precomputation, and that is all described above.
    */

    int n, m, q;
    cin >> n >> m >> q;
    vector<array<int, 3>> edges;
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        --a; --b;
        edges.push_back({a, b, w});
    }
    sort(edges.begin(), edges.end(), [](array<int, 3> a, array<int, 3> b){
        return a[2] < b[2];
    });
    // cout << "edges =\n";
    // for (auto edge : edges) {
    //     cout << "a="<<edge[0]<<", b="<<edge[1]<<", w="<<edge[2]<<"\n";
    // }

    vector<vector<vector<int>>> dist(m+1,
        vector<vector<int>>(n, vector<int>(n, 1e9)));
    for (int i = 0; i < n; ++i) {
        dist[0][i][i] = 0;
    }
    for (auto edge : edges) {
        int a = edge[0], b = edge[1];
        dist[0][a][b] = 1;
        dist[0][b][a] = 1;
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dist[0][i][j] = min(dist[0][i][j], dist[0][i][k] + dist[0][k][j]);
            }
        }
    }
    for (int thresholdidx = 1; thresholdidx <= m; ++thresholdidx) {
        auto edge = edges[thresholdidx-1];
        int a = edge[0], b = edge[1];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dist[thresholdidx][i][j] = min({
                    dist[thresholdidx-1][i][j],
                    dist[thresholdidx-1][i][a] + dist[thresholdidx-1][b][j],
                    dist[thresholdidx-1][i][b] + dist[thresholdidx-1][a][j]
                });
            }
        }
    }
    // for (int t = 0; t <= m; ++t) {
    //     cout << "for threshold = " << t;
    //     if (t < m) {
    //         cout << " (weight " << edges[t][2] << ")";
    //     }
    //     cout << "\n";
    //     for (int i = 0; i < n; ++i) {
    //         for (int j = 0; j < n; ++j) {
    //             cout << dist[t][i][j] << " ";
    //         }
    //         cout << "\n";
    //     }
    // }

    while (q--) {
        int a, b, k;
        cin >> a >> b >> k;
        --a; --b;
        int l = 0, r = m, weight = -1;
        while (l <= r) {
            int mid = l + (r-l)/2;
            if (dist[mid][a][b] < k) {
                weight = edges[mid-1][2];
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << weight << " ";
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
