#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n, m;
vector<vector<pair<int, int>>> adj;
vector<int> longestpath, pathsum;
vector<bool> visited;
map<int, unordered_set<int>> nodesperlength;
// orders nodes of same path length, based on lexicographical order of the paths themselves
unordered_map<int, vector<array<ll, 4>>> lexorder;
// maps a node to its index in the above order; not all nodes are in the same list
unordered_map<int, int> lexorderidx;
constexpr ll INF = 1e18;

template <typename T, size_t N>
std::ostream& operator<<(std::ostream &os, const array<T, N> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const vector<T> &c) {
    os << "[";
    for (const auto &elem : c) {
        os << elem << ",";
    }
    os << "]";
    return os;
}

void dfs(int node) {
    visited[node] = true;
    int maxnext = 0;
    for (auto next : adj[node]) {
        if (!visited[next.first]) {
            dfs(next.first);
        }
        maxnext = max(maxnext, longestpath[next.first]);
    }
    longestpath[node] = 1 + maxnext;
    nodesperlength[longestpath[node]].insert(node);
}

int main() {
    /*
    observations:
    - since computing the longest path starting from each node in a DAG is a known problem,
    we can just assume we can precompute that, and then try to solve the remaining problem
    under the assumption that we already have access to that information
    - if the nodes are sorted by topological ordering, then there is no guarantee that their
    longest path lengths are weakly decreasing. however, if the nodes are sorted in descending
    order by their longest path lengths, then it is guaranteed that they are in topological
    order.

    brute-force solution:
    - traverse through nodes in reverse topological order. for each node A, we want to construct the
    "longest-length, lexicographically smallest" path starting from it. (let's call it a "path of
    interest".) to do this, look at all adjacent nodes B_1, B_2, ..., B_k. we assume they've already
    been processed. among those, take the subset of them whose path of interest has maximum length
    among these nodes. among that subset, take the subset of them whose label of the edge A->B_i is
    minimum (since when lexicographically sorting paths, the first edge matters more than all others).
    now, among this subset, just sort the nodes lexicographically by corresponding path of interest,
    so then B_1's path will have A prepended to it to construct A's path of interest.
    - as for time complexity: i think the worst case is when N/2 nodes form a chain, and the other N/2
    nodes all point to the first node of the chain. then, comparison between 2 paths would be O(n), and
    there would be an O(n)-size set of paths to sort, so the cost would be O(n^2 log n).

    faster solution:
    - the slow part of the brute-force solution is sorting paths lexicographically. first, we can observe
    that we only ever need to compare the PATHS of nodes whose path of interest have the same length (for a
    node A, among all the adjacent nodes B_i, they might not have equal-length paths of interest, but if
    they don't, then we don't need to sort their paths; we just take the longer ones). this suggests
    precomputing the result of the comparison between nodes of the same interesting-path-length.
    alright, so then let longestpath(B_i) == longestpath(B_j). if label(A->B_i) != label(A->b_j), then we
    clearly know which edge will give us a lexicographically smaller path. however, if
    label(A->B_i) == label(A->B_j), then the information we want is that which tells us which of B_i or B_j
    has a lexicographically smaller path of interst starting from it. if we maintain this order some way, then
    we don't need to directly store the full paths themselves that start from B_i and B_j. we can just
    pick the node that has the smaller index in that order, and take the path sum as well.
    so, for each value L of longestpath, we can keep an order of the nodes who have that longest
    path length based on their lexicographical ordering.
    - in short, this is the optimization: the last part of comparing two nodes B_i and B_j which are both
    adjacent to A is to lexicographically compare their full paths, but if we precompute the order of paths
    across all nodes for the same path length (in particular, we care about the path length that B_i and B_j
    have), then that part is O(1).
    now, think of this as a subproblem. for all nodes {A_1, A_2, ..., A_k} of the same max-path-length, how
    can we sort them lexicographically by their paths? all the information we need is the label (weight) of
    the first outgoing edge for A_i on its interesting path and the index of the very next node on its path
    within the lexicographical order of paths for the next smaller path length. (note that when comparing
    A_i and A_j, if their max-path-length is L, the next node on A_i's max-length path and the next node on
    A_j's max-length path will each have a max-path-length of L-1, so that is why the 2 indices will both
    refer to the same order. if they weren't like this, then the indices would be useless, because they would
    refer to indices in different lists.) that's a RECURSIVE definition; what's the base case? nodes with
    max-path-length 0 can be ordered arbitrarily.
    simple clarification: why is the index important? if we sort things by some ordering, and then compare two
    of those things' indices in that sorted order, then we know which one is less and which is greater. in the
    editorial's solution code, this is denoted as `rnk[i]`. namely, if next(i) is the next node on the path
    of interest starting from i, then
    lexorderidx[i] = rank[i] = index of (label(i->next(i)), rank(next(i)), sum(path(i)), i)
    in a sorted list of (label(j->next(j)), rank(next(j)), sum(path(j)), j) across all j that have equal
    max-length-path to i.
    at a high level, the way that we compute rank[i] is by checking length(i), then checking label(i->next(i)),
    then checking rank[next(i)].
    - even shorter: we want to sort all nodes {A_1, A_2, ..., A_k} with max-path-length L based on their paths.
    how? standard way is to just sort their paths. efficient way is to sort by first element of path, and
    if they're equal, then to sort by index of second element of path in the list where all such second elements
    have been sorted by remaining part of path. the second elements can be assumed to be sorted properly, because
    there is a base case, which is that all elements with empty paths can be ordered arbitrarily.

    generalized ideas for the future:
    - if we want to fully compare two long things, we don't necessarily have to compare the full things.
    instead, we can compare the first element, and then use a pre-existing comparison between the rest
    of those things using DP. actually, now that i think about it, this probably only works for
    lexicographical comparison by definition.
    - in a multi-level comparison, where we first compare by one key, then a different key, then a
    different key, etc., it might be the case that some keys are much harder to compare by than others.
    in this problem, the sorting of adjacent nodes by max path length (specifically, among paths starting
    from each node) is easy, but if two nodes adjacent to the current node have equal max path length,
    then the process for lexicographically comparing their paths' labels is a lot more involved.
    - instead of storing, for each node, the full path starting from that node, which will then be used
    to compare against paths from other nodes, we can just construct the order resulting from this comparison
    directly (and the order is constructed recursively using this order for other nodes with shorter path).
        - nodes are only compared against other nodes that they need to be compared to (namely, the other
        nodes with equal max path length).
        - how to perform this comparison of paths without constructing the paths themselves? the paths are
        condensed into the only information needed (see below) to perform the comparison. specifically, the
        result of the comparison for everything beyond the first element (i.e., the first edge) is stored
        in the form of the indices.
    - it's okay to write up a solution with a lot of thought and effort, then to erase it and rewrite it
    to be more clear and understandable once again with a lot of thought and effort. in fact, it's probably
    better to have the second iteration be the one that gets saved, both because while writing it the clearer
    (and, more likely, more correct) ideas are going to get strengthened in my mind, and because it is easier
    to comprehend when looking back on it.
    - literally just like recursion, if you can define some property P of an element E in terms of either
    (1) the same property for another element, or (2) a base case, then that property is well-defined and
    can be computed. we just need to be able to make sure that calculating P(E) is not dependent on P(F)
    which then circularly becomes dependent on P(E) again, but this is taken care of in DAGs: a node is
    dependent on nodes it can reach, which are guaranteed to not be able to reach it.
    - it is a lot easier to reason about abstract things when intuitive names have been given to them.
    */

    // reads in input
    int n, m;
    cin >> n >> m;
    adj.resize(n);
    while (m--) {
        int a, b, l;
        cin >> a >> b >> l;
        --a; --b;
        adj[a].push_back(make_pair(b, l));
    }

    // implicitly gets topsort, but more importantly gets longest paths
    visited = vector<bool>(n, false);
    longestpath.resize(n);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    // iterates through path lengths, and for each, it goes through all nodes with that path length
    // and determines that node's path. that's what it does at a high level, but in the implementation,
    // it determines just enough information about that node's path for the node to be sorted against
    // other nodes with the same max length
    for (auto entry : nodesperlength) {
        int length = entry.first;

        // given nodes {n_1, n_2, ..., n_k}, we already know that their max path lengths
        // are all equivalent. we want to order the nodes by their max-length paths (lexicographically).
        // to do this, for a node n_i, we condense the path into the only information from it we need:
        // the first edge on that path [n_i, n_j], the index of the next node after that first edge (so n_j)
        // in the lexicographical order of all nodes with same max-path-length as n_j, the sum of labels
        // on that path, and the node n_i itself.

        // what's the significance of the index of n_j across nodes with same max-path-length as n_j?
        // it basically does the rest of the lexicographical comparison (beyond the first edge out from
        // n_i) for us.
        lexorder[length] = vector<array<ll, 4>>();
        for (int node : entry.second) {
            // this process simply picks the next node of `node` on `node`'s path of interest, and what
            // that means is that we also gather enough information about the path going out from `node`
            // to be able to sort `node` against other nodes of the same max-path-length
            array<ll, 4> arr{INF, INF, 0, node}; // label of first edge, index of node after first edge, path sum, orig node
            for (auto next : adj[node]) {
                if (
                    longestpath[next.first] == length-1 &&  // first, sort by length of path
                    (
                        next.second < arr[0] ||  // then, sort by first edge of path
                        (next.second == arr[0] && lexorderidx[next.first] < arr[1])  // then, sort by sorted order of remaining part of path
                    )
                ) {
                    arr[0] = next.second;
                    arr[1] = lexorderidx[next.first];
                    arr[2] = next.second + lexorder[longestpath[next.first]][lexorderidx[next.first]][2];
                }
            }
            lexorder[length].push_back(arr);
        }
        sort(lexorder[length].begin(), lexorder[length].end());

        // gets each node's index in the lexicographical order
        for (int i = 0; i < lexorder[length].size(); ++i) {
            lexorderidx[lexorder[length][i][3]] = i;
        }
    }

    // outputs answers
    for (int i = 0; i < n; ++i) {
        array<ll, 4> pathinfo = lexorder[longestpath[i]][lexorderidx[i]];
        cout << (longestpath[i] - 1) << ' ' << pathinfo[2] << '\n';
    }
}
