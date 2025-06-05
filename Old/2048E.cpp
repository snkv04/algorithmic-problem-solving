#include <bits/stdc++.h>
using namespace std;

using ll = long long;
int MOD = (int) 1e9 + 7; // 998244353;
int di[] = {0, 0, 1, -1}, dj[] = {1, -1, 0, 0};

void solve() {
    /**
     * based on the fact that we cannot have cycles for each color, the subgraph formed
     * by the edges of each color must be a tree or forest. additionally, based on this,
     * we can determine a bound on the size of m that allows for such a forest to exist.
     * now, we can find a method of constructing the graph itself. each vertex on the
     * left has a degree of m, and each vertex on the right has a degree of 2n, where there
     * are exactly n colors allowed in the graph. one way to construct the graph is to
     * make each vertex on the right have exactly 2 edges of each color. this way, for
     * any given color i, where i ranges from 1 to n, we start at the (2i-1)th vertex from
     * the top on the left side, go to the top vertex on the right side, and continue to
     * make a "chain" from there, going down by 1 each time we switch sides (ending once
     * we've gotten 2m edges for that color). this way, it makes sense that we can't have
     * m any greater than 2n-1, because if we did, then the chain would connect and it
     * would become a loop.
     * 
     * how exactly could you come up with this bound? what if the condition for being
     * able to construct the graph wasn't a simple check for being above or below a bound?
     * it comes from the fact that if we know each color forms a forest, then we can
     * maximize the number of edges by making it a tree, fixing n and finding the maximum
     * m (or vice versa). in this case, fixing one variable and then looking at the other
     * works, though in some problems the variables constrain each other. anyway, this
     * gives a straight up simple inequality by combining some information about the
     * number of edges and vertices, and we could see that that inequality is the entire
     * condition we need by observing that it is impossible after m reaches a certain
     * value but it is always possible, through the pattern used in the problem, if m
     * is lower than that. i guess it could also just be guessed that the inequality
     * found is the only condition we need to care about, though that is not as helpful
     * for the future.
     * 
     * why are we assigning exactly 2 edges of each color for each vertex on the right?
     * on a related note, how exactly could you come up with this graph?
     * so, one of the corollaries of the setup given in the problem is that each left
     * vertex has a degree of m and each right vertex has a degree of 2*n. since there
     * are at most n colors, it's just a simple hypothesis that among each right vertex's
     * 2n adjacent edges, n of them belong to each color to allow each color to have an
     * analogous, symmetric pattern. yes, making hopeful hypotheses based on symmetry
     * will not always work in every problem, but it is something to try.
     * there are a variety of things that could be tried. having a star graph for each
     * of the vertices on the left or right pretty quickly runs into cycles. having
     * chains like in the final solution but having the chain for color i start at
     * vertex i on the left repeats vertices. having chains that jump down by 2 on
     * each side every time it switches sides also repeats edges (and, as a result,
     * skips some others).
     * so, we can try starting chain for color i at vertex 2i-1 on the left. remember
     * that for any given color n we have 2m edges, so by moving down by 1 each time
     * we switch sides, we touch every vertex on the right side (twice) but touch
     * different vertices on the left (for any given vertex on the right). again, since
     * the number of edges for any color is 2m (which can at most be 2*(2n-1), or 2
     * times one less than the number of vertices on the left), we know that the chains
     * formed by any one of the colors will never form a cycle. so, if the start points
     * are properly set up so that none of the chains are overlapping, then we know
     * we aren't repeating any vertices. also, since n*2m is equal to 2nm, it's clear
     * that this is, in fact, catching all the possible edges (as it effectively is
     * one way to make each vertex on the right be adjacent to every vertex on the
     * left).
     * these are all really just motivated by heuristics and "would-be-nice" guesses
     * on what the solution would look like, based on the given properties. they aren't
     * out of the realm of possibility, because these are problems meant to be solved
     * in a contest, so using simple structures and patterns is likely, but i guess
     * it just means that combining all the known properties and then proceeding to
     * do trial-and-error to find the simplest, most elegant WORKING structure is the
     * way to solve this problem.
     * 
     * what were the hardest observations to come to that would give this problem its
     * rating of 2000?
     * they're all honestly fairly simple observations, but the main difficult thing is
     * figuring out which pieces of information will end up being useful.
     * the initial jump between "no cycles for any color" to "each color is a forest/tree"
     * is not really difficult, so i should probably mentally associate those two definitions
     * more.
     * maybe experience is also something that makes it easier to select which of the most
     * common tree structures is to be used, though it's not too hard to arrive at through
     * trial-and-error.
     * i think one thing that should be more intuitive to me is the fact that the thing which
     * makes a graph under these conditions not possible is whether or not a single color is
     * able to go through all m vertices (twice) given 2n vertices on the left, and that
     * having a cycle-less graph when the vertices on both sides is equal (or there's more on
     * the right) is impossible if we need 2m edges for that color. the number of edges that
     * each color is able to "hold" is directly tied to being able to fit all the edges under
     * at most n colors, which is more directly the question that the problem is asking. this
     * is an intuitive justification for the more mathematical statement that's represented
     * by the derived inequality (m < 2*n).
     * 
     * how to arrive at the more elegant way to code this?
     * it's really more of an afterthought than anything else, as opposed to being a
     * core part of the problem. it's simply an optimization done by looking at the pattern
     * formed from the edges that each color gets assigned to and then making a mathematical
     * formula out of it, which doesn't really cause much more of an optimization than
     * a constant-time one (though this process can have a more important impact in
     * other problems).
     * 
     * any other useful things to remember?
     * this is kind of obvious when looking at it on its own, but when constructing a
     * graph with a zigzag kind of pattern (which is basically just what a path would
     * usually look like in a bipartite graph), the end of the zigzag connecting back
     * to the beginning automatically forms a cycle.
     * also, if a graph is restricted to only being a forest (no cycles), then if you
     * want to maximize the number of edges in the graph, it will end up being a tree.
     */

    int n, m;
    cin >> n >> m;
    if (m >= 2*n) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    for (int i = 1; i <= 2*n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cout << (((i + 2*n - j) % (2 * n)) / 2) + 1 << " ";
        }
        cout << "\n";
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
