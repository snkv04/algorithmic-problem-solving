import java.util.*;
import java.io.*;

public class WormholeSort4 {
    static int n, m;
    static int[] p;
    static ArrayList<Edge>[] adj;
    static ArrayList<Integer>[] updatedAdj;
    static boolean[] visited;
    static HashSet<Integer> nodes, pNodes; // all nodes found in connected component

    public static void main(String[] args) throws IOException{
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("wormsort.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("wormsort.out")));

        String[] line = br.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        m = Integer.parseInt(line[1]);
        p = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        for (int i =0 ;i <= n-1 ;i++) p[i]--;
        adj = new ArrayList[n]; for (int i = 0; i <= n-1; i++) adj[i] = new ArrayList<>();
        for (int i = 1; i <= m; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0])-1;
            int b = Integer.parseInt(line[1])-1;
            int w = Integer.parseInt(line[2]);
            adj[a].add(new Edge(b, w));
            adj[b].add(new Edge(a, w));
        }

        int l = 0, r = (int) (1e9 + 6), ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(mid)) {
                ans = mid;
                l = mid+1;
            } else {
                r = mid-1;
            }
        }
        pw.println(ans==(int)1e9+6?-1:ans);;

        br.close(); pw.close();
    }
    
    static class Edge {
        int to, weight;

        public Edge(int to, int weight) {
            this.to = to;
            this.weight = weight;
        }
    }

    static boolean check(int minWeight) {
        updatedAdj = new ArrayList[n];
        visited = new boolean[n];
        for (int i = 0; i <= n-1; i++) {
            updatedAdj[i] = new ArrayList<>();
        }
        for (int i = 0; i <= n-1; i++) {
            for (Edge e : adj[i]) {
                if (e.weight >= minWeight) {
                    updatedAdj[i].add(e.to);
                }
            }
        }


        for (int i = 0; i <= n-1; i++) {
            nodes = new HashSet<>(); pNodes = new HashSet<>();
            if (!visited[i]) dfs(i);

            if (nodes.size() != pNodes.size()) return false;
            for (int node : nodes) if (!pNodes.contains(node)) return false;
        }

        return true;
    }

    static void dfs(int node) {
        visited[node] = true;
        nodes.add(node);
        pNodes.add(p[node]);
        for (int next : updatedAdj[node]) if (!visited[next]) dfs(next);
    }
}
