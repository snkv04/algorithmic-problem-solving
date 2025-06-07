import java.util.*;
import java.io.*;

public class ErodingPillars {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static ArrayList<Edge> edges;
    static int n;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t =  1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        n = Integer.parseInt(br.readLine());
        double[][] coords = new double[n+1][2];
        for (int i = 0; i <= n-1; i++) {
            coords[i] = Arrays.stream(br.readLine().split(" ")).mapToDouble(Integer::parseInt).toArray();
        }
        coords[n][0] = 0; coords[n][1] = 0;

        edges = new ArrayList<>();
        for (int i = 0; i <= n ;i++) {
            for (int j = i+1; j <= n; j++) {
                double dist = Math.sqrt(Math.pow(coords[j][0]-coords[i][0], 2) + Math.pow(coords[j][1] - coords[i][1], 2));
                edges.add(new Edge(i, j, dist));
            }
        }
        edges.sort(Comparator.comparingDouble(e -> e.weight));

        int l = 0, r = edges.size()-1, index = -1;
        while (r >= l) {
            int mid = (l+r)/2;
            if (check(edges.get(mid).weight)) {
                index = mid;
                r = mid-1;
            } else {
                l = mid+1;
            }
        }
        pw.println(edges.get(index).weight);
    }

    static ArrayList<Integer>[] adj;
    static int[] preorder, low;
    static TreeSet<Integer> articulationPoints;
    static int counter;

    static boolean check(double maxDist) {
        adj = new ArrayList[n+1]; for (int i = 0; i <= n; i++) adj[i] = new ArrayList<>();
        for (Edge e : edges) {
            if (e.weight <= maxDist) {
                adj[e.a].add(e.b);
                adj[e.b].add(e.a);
            } else {
                break;
            }
        }

        preorder = new int[n+1]; low = new int[n+1]; counter = 0;
        Arrays.fill(preorder, -1);
        articulationPoints = new TreeSet<>();
        int dfsCounts = 0; // if it ends up equalling 1, then the graph is connected
        for (int i = 0; i <= n; i++) {
            if (preorder[i] == -1) {
                dfsCounts++;
                // pw.println("running dfs from node i="+i);
                dfs(i, i);
            }
        }

        if (dfsCounts != 1) return false;
        if (articulationPoints.size() == 0) return true;
        else if (articulationPoints.size() == 1 && articulationPoints.first() == n) return true;
        else return false;
    }

    static void dfs(int node, int child) {
        if (articulationPoints.size() > 1) return;
        preorder[child] = counter;
        low[child] = counter;
        counter++;
        int children = 0;

        for (int next : adj[child]) {
            if (preorder[next] == -1) {
                children++;
                dfs(child, next);
                low[child] = Math.min(low[child], low[next]);
                if (node != child && low[next] >= preorder[child]) {
                    articulationPoints.add(child);
                }
            } else if (next != node) {
                low[child] = Math.min(low[child], low[next]); // the second parameter can either be pre[next] or low[next]
            }
        }

        if (child == node && children > 1) {
            articulationPoints.add(node);
        }
    }

    static class Edge {
        int a, b;
        double weight;

        public Edge(int a, int b, double weight) {
            this.a = a;
            this.b = b;
            this.weight = weight;
        }
    }
}
