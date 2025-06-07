import java.util.*;
import java.io.*;

public class MovieNight {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static ArrayList<Integer>[] adj, adj2;
    static HashSet<HashSet<Integer>> components;
    static boolean[] visited;
    static HashSet<Integer> comp;
    // static HashMap<Integer, Boolean> visited2;
    static int counter;
    static int[] pre, low;
    static Stack<Integer> stack;
    static boolean[] onStack;
    static HashSet<Integer> currComp;
    static int[] outdegree;
    static int n;

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
        n = Integer.parseInt(br.readLine());
        adj = new ArrayList[n]; adj2 = new ArrayList[n];
        outdegree = new int[n];
        for (int i = 0; i <= n-1; i++) {
            adj[i] = new ArrayList<>(); adj2[i] = new ArrayList<>();
        }
        for (int i = 0;i <= n-1; i++) {
            int to = Integer.parseInt(br.readLine()) - 1;
            adj[i].add(to);
            adj2[to].add(i); // is the reverse (or "transpose") graph
            outdegree[i]++;
        }

        // separates the graph into weakly connected components
        components = new HashSet<>();
        visited = new boolean[n];
        for (int i = 0; i <= n-1; i++) {
            if (!visited[i]) {
                comp = new HashSet<>();
                dfs(i);
                components.add(comp);
            }
        }

        // puts the number of possibilities from each component (including
        // having none of the nodes) into the list, where run() operates on
        // each weakly connected component separately
        ArrayList<Long> counts = new ArrayList<>();
        for (HashSet<Integer> component : components) {
            counts.add(1 + run(component));
        }

        // multiplies them all together, and subtracts the single empty subset case
        long count = counts.get(0);
        for (int i = 1; i <= counts.size() - 1; i++) {
            count *= counts.get(i);
            count %= MOD;
        }
        count -= 1;
        pw.println(count);
    }

    // utility function to split the graph into weakly connected components
    static void dfs(int node) {
        visited[node] = true;
        comp.add(node);
        for (int next : adj[node]) {
            if (!visited[next]) {
                dfs(next);
            }
        }
        for (int next : adj2[node]) {
            if (!visited[next]) {
                dfs(next);
            }
        }
    }

    // first runs Tarjan's, then removes all nodes in cycles, before finding
    // the number of ways to select the nodes not in cycles
    static long run(HashSet<Integer> component) {
        pre = new int[n];
        low = new int[n];
        Arrays.fill(pre, -1);
        Arrays.fill(low, -1);

        counter = 0;
        stack = new Stack<>();
        onStack = new boolean[n];
        currComp = component;
        for (int node : component) {
            if (pre[node] == -1) {
                dfs2(node);
            }
        }

        // maps each low-link value (SCC identifier) to the nodes that have it
        HashMap<Integer, ArrayList<Integer>> lows = new HashMap<>();
        for (int node : component) {
            if (!lows.containsKey(low[node])) lows.put(low[node], new ArrayList<>());
            lows.get(low[node]).add(node);
        }

        // detects the singular cycle in the weakly connected component by looking
        // at the low-link value with more than one node in it
        for (Map.Entry<Integer, ArrayList<Integer>> entry : lows.entrySet()) {
            if (entry.getValue().size() > 1) {
                for (int node : entry.getValue()) {
                    currComp.remove(node);
                    for (int from : adj2[node]) outdegree[from]--;
                }
                break;
            }
        }

        // for each tree branching out from the cycle (using the transpose of the
        // given directed graph), count the number of subsets that follow the condition
        // that every node needs its parent to be selected if it's not the root
        long product = 1;
        for (int node : currComp) {
            if (outdegree[node] == 0) {
                product *= (long) 1 + ways(node);
                product %= MOD;
            }
        }
        return product;
    }

    // utility function for Tarjan's
    static void dfs2(int node) {
        pre[node] = counter;
        low[node] = counter++;
        stack.add(node);
        onStack[node] = true;

        for (int next : adj[node]) {
            if (!currComp.contains(next)) continue;
            
            if (pre[next] == -1) {
                dfs2(next);
            }

            if (onStack[next]) {
                low[node] = Math.min(low[node], low[next]);
            }
        }

        if (pre[node] == low[node]) {
            while (true) {
                int top = stack.pop();
                onStack[top] = false;

                if (top == node) return;
            }
        }
    }

    // counts the number of possibilities with this subtree branching off
    static long ways(int node) {
        long ways = 1;
        // pw.println("visiting "+node);
        for (int next : adj2[node]) {
            ways *= 1 + ways(next);
            ways %= MOD;
        }
        // pw.println("leaving " + node);
        return ways;
    }
}
