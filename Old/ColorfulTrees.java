import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class ColorfulTrees {
    // static BufferedReader br;
    // static PrintWriter pw;
    // static int MOD = (int) (1e9 + 7); // 998244353;
    // static int[] di = {0, 0, 1, -1}, dj = {1, -1, 0, 0};
    // static ArrayList<Integer>[] adj;
    // static int[] colors;
    // static HashMap<String, Long> ans;
    // static Multiset rightColors, leftColors;
    // static long pairs;

    // public static void main(String[] args) throws IOException {
    //     br = new BufferedReader(new InputStreamReader(System.in));
    //     pw = new PrintWriter(System.out);

    //     int t = 1;
    //     while (t-->0) {
    //         solve();
    //     }

    //     br.close(); pw.close();
    // }

    // static void solve() throws IOException {
    //     /*
    //      * first look at the single edge. get teh multisets all ready and calculate everything.
    //      * then repeatedly reroot the tree. get each one in O(1) time.
    //      * 
    //      * first, look at the first edge. make a dfs that accepts a ndoe and a parent.
    //      * dfs on the right side, adding each color to the "right" multiset of colors (colors
    //      * themselves will map to their own frequencies). same thing for left. how can we 
    //      * do that? for right, dfs on the right node with the left node as the parent, so we
    //      * don't go back ont he left. for each node that's adjacent (EXCEPT the parent), we 
    //      * dfs onto it. it's pretty easy.
    //      * after we get the right and left, just calculate all the combinations. for ease, just
    //      * map the edge as a string to its answer. USE LONGS!
    //      * 
    //      * now, for rerooting. consider a dfs that accepts an edge (in the form of two nodes), and
    //      * a "DON'T GO BACK" node, which is one of the two ends. start from the first edge (arbitrary).
    //      * move to the left with this dfs, removing the node that was crossed from the left multiset
    //      * and adding it to the right. since only that one was the only color that changed, we can
    //      * just recalculate (subtract then add) for that color. dfs to the edge. going back (i.e., after
    //      * the call is done), undo the change. for the edge case (there are no more edges for the node
    //      * we stepped over), it can handle it by itself. for calculations, we do it for any given edge
    //      * in the function that calls DFS for that edge. now for defining dfs, we can step over the left
    //      * node first, going through all of its adjacent nodes directly from here (the current node), and
    //      * then step over the left node. the left/right order is arbitrary.
    //      */
    //     int n = Integer.parseInt(br.readLine());
    //     adj = new ArrayList[n]; for (int i = 0; i < n; i++) adj[i] = new ArrayList<>();
    //     colors = new int[n];
    //     for (int i = 0; i < n; i++) {
    //         colors[i] = Integer.parseInt(br.readLine());
    //     }
    //     System.out.println("colors = "+Arrays.toString(colors));

    //     ans = new HashMap<>();
    //     int l = -1, r = -1;
    //     for (int i = 0; i < n-1; i++) {
    //         String[] s = br.readLine().split(" ");
    //         System.out.println("s = "+Arrays.toString(s));
    //         int a = Integer.parseInt(s[0]) - 1, b = Integer.parseInt(s[1]) - 1;
    //         if (i == 0) {
    //             l = a;
    //             r = b;
    //         }
    //         adj[a].add(b);
    //         adj[b].add(a);
    //         ans.put(a+" "+b, (long)0);
    //     }
    //     pw.println("l="+l+", r="+r);

    //     rightColors = new Multiset(); leftColors = new Multiset();
    //     dfs(r, l, true);
    //     dfs(l, r, false);
    //     // pw.println("leftcolors = "+leftColors.mset+", rightcolors = "+rightColors.mset);

    //     pairs = 0;
    //     for (Map.Entry<Integer, Integer> entry : leftColors.mset.entrySet()) {
    //         pairs += (long) entry.getValue() * (long) rightColors.count(entry.getKey());
    //     }
    //     ans.put(l+" "+r, pairs);
    //     pw.println("for l="+l+", r="+r+", we have pairs="+pairs);
    // }

    // static void dfs(int node, int parent, boolean right) {
    //     if (right) {
    //         rightColors.add(colors[node]);
    //     } else {
    //         leftColors.add(colors[node]);
    //     }

    //     for (int next : adj[node]) {
    //         if (next != parent) {
    //             dfs(next, node, right);
    //         }
    //     }
    // }

    // static void dfs2(int l, int r, boolean right) {
    //     if (!right) {
    //         pairs -= leftColors.count(l) * rightColors.count(l);
    //         leftColors.remove(l);
    //         rightColors.add(l);
    //         pairs += leftColors.count(l) * rightColors.count(l);
    //         for (int next : adj[l]) {
    //             if (next == r) continue;
    //             dfs2(next, l, right);
    //         }
    //         pairs -= leftColors.count(l) * rightColors.count(l);
    //         rightColors.remove(l);
    //         leftColors.add(l);
    //         pairs += 
    //     }
    // }

    static BufferedReader br;
    static PrintWriter pw;
    static int[] totalCounts;
    static ArrayList<Edge>[] adj;
    static Multiset[] subtreeColorCounts;
    static long[] subtreePairs;
    static long[] answers;

    public static void main(String[] args) throws Exception {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close();
        pw.close();
    }

    static void solve() throws IOException {
        /*
         * first, go through the entire tree and build the map of the total counts for all colors
         * also, set up a map from edge to answer so that the ordering later can be easily dealt with
         * now, do a postorder dfs to get the answers:
         *      for each subtree, we want to have a count of each color within that subtree
         *      we also want the number of pairs
         *      for a given subtree, look at all the children (and the root). pick the largest map
         *          by number of key-value pairs.
         *      for the subtree, go through all of the colors for the other maps, and merge them into
         *          the largest map, updating the number of pairs accordingly. after this is done, the
         *          answer for the edge that connects this subtree to the rest of the tree is decided
         * finally, go through the edges in the original order and print out the answers
         */
        FastScanner fs = new FastScanner();

        int n = fs.nextInt();

        totalCounts = new int[n+1];
        subtreeColorCounts = new Multiset[n]; for (int i = 0; i < n; i++) subtreeColorCounts[i] = new Multiset();
        subtreePairs = new long[n];

        for (int i = 0; i < n; i++) {
            int color = fs.nextInt();
            totalCounts[color] += 1;
            subtreeColorCounts[i].add(color);
        }
        for (int i = 0; i < n; i++) {
            int onlyColor = -1;
            for (Map.Entry<Integer, Integer> entry : subtreeColorCounts[i].map.entrySet()) {
                onlyColor = entry.getKey();
                break;
            }
            subtreePairs[i] = 1 * (totalCounts[onlyColor] - 1);
            /*
             * this part might not make intuitive sense at first, since we generally
             * want subtreePairs[i] to represent the numbers of pairs possible by using the colors
             * in the subtree paired with the colors outside of the subtree. so, setting each
             * subtreePairs[i] value equal to the number of pairs using only that node and the rest
             * of the whole tree might not make sense, since a single node isn't equal to the whole
             * subtree with that node as the root. however, since in the calculations of pairs we
             * do the whole subtracting the number of pairs derived from the old count and adding
             * the number of pairs derived from the new count to "update" the number of pairs,
             * the root node for the current subtree being looked at in the dfs() method is unique
             * compared to the children subtrees. keeping the root node separate from all the children
             * subtrees being looked at, it's clear that the root node only has itself as the initial
             * set of nodes which it includes for its initial pairs calculation (not counting anything
             * OUTSIDE the whole subtree we are looking at with the current node as the root node). so,
             * to have it work the same as the children nodes for the pairs calculations while merging
             * the maps together, the count of pairs for every single node in the tree should first
             * assume that the node itself is its own subtree (even though once we root the tree at
             * 0, each node has its own whole subtree that is likely not just itself). so, just to
             * be clear, we treat each node as its own "subtree" just for the sake of initializing
             * the values to work properly for the pairs calculation when merging the maps together,
             * even though the nodes are not actually their own subtrees unless they are leaves.
             */
        }
        // pw.println("totalCounts = "+totalCounts.map);
        // pw.println("subtreeColorCounts = "+Arrays.toString(Arrays.stream(subtreeColorCounts).map(o -> o.map).toArray()));

        int[][] edges = new int[n-1][2];
        adj = new ArrayList[n]; for (int i = 0; i < n; i++) adj[i] = new ArrayList<Edge>();
        for (int i = 0; i < n-1; i++) {
            int a = fs.nextInt() - 1, b = fs.nextInt() - 1;
            edges[i][0] = a; edges[i][1] = b;
            adj[a].add(new Edge(b, i));
            adj[b].add(new Edge(a, i));
        }

        answers = new long[n-1];
        dfs(0, -1, -1);
        // pw.println("after calling dfs(), subtreeColorCounts = "+Arrays.toString(Arrays.stream(subtreeColorCounts).map(o -> o.map).toArray()));

        for (int i = 0; i < n-1; i++) {
            pw.println(answers[i]);
        }
        // pw.println(answers);
    }

    static void dfs(int node, int parent, int idx) {
        /*
         * first, look over the children and the current node and identify where is the largest map.
         * then, take that map and that number of pairs, and merge all of the others into it, updating
         * the pairs as well. the final map and num of pairs will be assigned to the current node.
         * return nothing.
         */
        int largestMapNode = node;
        for (Edge e : adj[node]) {
            if (e.to != parent) {
                dfs(e.to, node, e.idx);
                if (subtreeColorCounts[e.to].map.size() > subtreeColorCounts[largestMapNode].map.size()) {
                    largestMapNode = e.to;
                }
            }
        }

        long pairs = subtreePairs[largestMapNode];
        // pw.println("before any merging, for the map "+largestMap.map+", the num of pairs is "+pairs);
        for (Edge e : adj[node]) {
            int next = e.to;
            if (next != parent && next != largestMapNode) {
                int other = next;
                if (subtreeColorCounts[next].map.size() > subtreeColorCounts[largestMapNode].map.size()) {
                    other = largestMapNode;
                    largestMapNode = next;
                    pairs = subtreePairs[largestMapNode];
                }
                // pw.println("about to merge "+subtreeColorCounts[next].map+" into "+largestMap.map);
                for (Map.Entry<Integer, Integer> entry : subtreeColorCounts[other].map.entrySet()) {
                    int color = entry.getKey(), count = entry.getValue();
                    pairs -= (long) subtreeColorCounts[largestMapNode].count(color) * (long) (totalCounts[color] - subtreeColorCounts[largestMapNode].count(color));
                    subtreeColorCounts[largestMapNode].add(color, count);
                    pairs += (long) subtreeColorCounts[largestMapNode].count(color) * (long) (totalCounts[color] - subtreeColorCounts[largestMapNode].count(color));
                }
                // pw.println("after merging, largestmap = "+largestMap.map);
            }
        }
        if (largestMapNode != node) {
            int other = node;
            if (subtreeColorCounts[node].map.size() > subtreeColorCounts[largestMapNode].map.size()) {
                other = largestMapNode;
                largestMapNode = node;
                pairs = subtreePairs[largestMapNode];
            }
            for (Map.Entry<Integer, Integer> entry : subtreeColorCounts[other].map.entrySet()) {
                int color = entry.getKey(), count = entry.getValue();
                pairs -= (long) subtreeColorCounts[largestMapNode].count(color) * (long) (totalCounts[color] - subtreeColorCounts[largestMapNode].count(color));
                subtreeColorCounts[largestMapNode].add(color, count);
                pairs += (long) subtreeColorCounts[largestMapNode].count(color) * (long) (totalCounts[color] - subtreeColorCounts[largestMapNode].count(color));
            }
        }

        subtreeColorCounts[node] = subtreeColorCounts[largestMapNode];
        subtreePairs[node] = pairs;
        // pw.println("for the map "+largestMap.map+", pairs = "+pairs);
        if (idx != -1) answers[idx] = pairs;
    }

    static class Edge {
        int to, idx;

        public Edge(int to, int idx) {
            this.to = to;
            this.idx = idx;
        }
    }

    // // // //

    static class Multiset {
        TreeMap<Integer, Integer> map = new TreeMap<>();

        public void add(int x) {
            if (map.containsKey(x)) {
                map.put(x, map.get(x) + 1);
            } else {
                map.put(x, 1);
            }
        }
        
        public void remove(int x) {
            map.put(x, map.get(x) - 1);
            if (map.get(x) == 0) map.remove(x);
        }

        public void add(int x, int q) {
            // q for quantity
            if (map.containsKey(x)) {
                map.put(x, map.get(x) + q);
            } else {
                map.put(x, q);
            }
        }

        public int count(int x) {
            if (!map.containsKey(x)) {
                return 0;
            } else {
                return map.get(x);
            }
        }
    }

    public static class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        public FastScanner(Reader r) {
            br = new BufferedReader(r);
        }

        public FastScanner() { this(new InputStreamReader(System.in)); }

        public String next() {
            while (st == null || !st.hasMoreTokens()) {
                try {
                    st = new StringTokenizer(br.readLine());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            return st.nextToken();
        }

        public int nextInt() { return Integer.parseInt(next()); }
        public long nextLong() { return Long.parseLong(next()); }
        public double nextDouble() { return Double.parseDouble(next()); }

        public String readNextLine() {
            String str = "";
            try {
                str = br.readLine();
            } catch (IOException e) {
                e.printStackTrace();
            }
            return str;
        }

        public int[] readIntArray(int n) {
            int[] a = new int[n];
            for (int i = 0; i < n; i++) {
                a[i] = nextInt();
            }
            return a;
        }
    }
}
