import java.util.*;
import java.io.*;

public class BranchManager {
    static BufferedReader br;
    static PrintWriter pw;
    static TreeSet<Integer>[] graph;
    static int[] transpose;
    static int[] leftmost;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        // The problem can be reformulated as follows: Given a directed tree,
        // rooted at node 1 and having all edges directed away from the root,
        // and given m queries, find the size of the largest prefix of the
        // queries such that each query's node lies along the leftmost path
        // possible in the tree, such that the children of each node are ordered
        // in increasing order. If a query node is reachable but not on the
        // leftmost path through the tree, then delete all necessary subtrees
        // to ensure that node is on the leftmost path. If the node is not
        // reachable, then the remaining suffix of queries is not considered,
        // and the size of the prefix so far is outputted.

        // takes input
        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        graph = new TreeSet[n];
        for (int i = 0; i <= n-1; i++) graph[i] = new TreeSet<>();
        transpose = new int[n]; // transpose of the directed tree
        Arrays.fill(transpose, -1);
        for (int i = 1; i <= n-1; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0])-1;
            int b = Integer.parseInt(line[1])-1;
            graph[a].add(b);
            transpose[b] = a;
        }
        int[] destinations = new int[m];
        for (int i= 0; i <= m-1; i++) {
            destinations[i] = Integer.parseInt(br.readLine()) - 1;
        }
        leftmost = new int[n];
        leftmost[0] = 1;
        dfs(0); // marks all nodes on the leftmost path

        // now, goes through all queries
        int ans = 0;
        for (int dest : destinations) {
            // if a node is no longer reachable (meaning that the path to it
            // from the root has been closed down in earlier queries), then
            // the algorithm is done
            if (transpose[dest] == -1) {
                break;
            }

            // here, we already know that the node is at least reachable, so if
            // it isn't on the desired path, then we remove all nodes which
            // cause that to be the case
            if (leftmost[dest] != 1) {
                // constructs the path up from the current node until the point
                // in the path (between the current node and the root) where the
                // path diverges from the leftmost path
                int curr = dest;
                Stack<Integer> path = new Stack<>();
                while (leftmost[curr] != 1) {
                    path.add(curr);
                    curr = transpose[curr];
                }

                // on each level of depth from topmost to bottommost (maybe this
                // order isn't important), all nodes to the left of the node on the
                // path being currently considered are removed from the graph, also
                // unmarking those as leftmost and marking the current node on the
                // path as leftmost
                while (!path.isEmpty()) {
                    int nextCity = path.pop();
                    while (graph[curr].first() != nextCity) {
                        dfs2(graph[curr].pollFirst());
                    }
                    curr = nextCity;
                    leftmost[nextCity] = 1;
                }
            }
            ans++;
        }
        pw.println(ans);
    }

    // is used to mark all nodes on the leftmost path
    static void dfs(int node) {
        if (node != 0) {
            // if a node's parent is on the leftmost path and the current node is the
            // numerically least child node of its parent, then it's on the leftmost
            // path, otherwise it isn't
            if (graph[transpose[node]].first() == node && leftmost[transpose[node]] == 1) {
                leftmost[node] = 1;
            } else {
                leftmost[node] = 0;
            }
        }

        for (int next : graph[node]) {
            dfs(next);
        }
    }

    // is used to delete subtrees
    static void dfs2(int node) {
        // first, this method is recursively applied to all children of the node
        for (int next : graph[node]) {
            dfs2(next);
        }

        // sets parent to -1 (essentially a null value), clears its children, and
        // removes it from the leftmost path
        transpose[node] = -1;
        graph[node].clear();
        leftmost[node] = 0;
    }
}
