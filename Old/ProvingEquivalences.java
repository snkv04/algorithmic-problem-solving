import java.util.*;
import java.io.*;

public class ProvingEquivalences {
    static BufferedReader br;
    static PrintWriter pw;
    static ArrayList<Integer>[] graph;
    static ArrayList<Integer>[] transposeGraph;
    static ArrayList<Integer> reverseTopological;
    static boolean[] visited;
    static int[] scc;
    static TreeMap<Integer, TreeSet<Integer>> nodesInSCC;
    static ArrayList<Integer>[] condensed;
    static TreeSet<Integer> reachableOnPath;
    static int[] in, out;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine()); // 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        graph = new ArrayList[n]; transposeGraph = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) {
            graph[i] = new ArrayList<>();
            transposeGraph[i] = new ArrayList<>();
        }
        for (int i = 1; i <= m; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]) - 1;
            int b = Integer.parseInt(line[1]) - 1;
            graph[a].add(b);
            transposeGraph[b].add(a);
        }

        visited = new boolean[n];
        reverseTopological = new ArrayList<Integer>();
        for (int i = 0; i <= n-1; i++) if (!visited[i]) dfs(i);
        visited = new boolean[n];
        scc = new int[n];
        for (int i = n-1; i >= 0; i--) {
            int node = reverseTopological.get(i);
            if (!visited[node]) dfs2(node, node);
        }

        condensed = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) condensed[i] = new ArrayList<Integer>();
        nodesInSCC = new TreeMap<Integer, TreeSet<Integer>>();
        for (int i = 0; i <= n-1; i++) {
            for (int adjacent : graph[i]) {
                if (scc[i] != scc[adjacent]) {
                    condensed[scc[i]].add(scc[adjacent]);
                }
            }

            if (!nodesInSCC.containsKey(scc[i])) nodesInSCC.put(scc[i], new TreeSet<>());
            nodesInSCC.get(scc[i]).add(i);
        }

        visited = new boolean[n];
        in = new int[n]; out = new int[n];
        for (int i = 0 ;i <= n-1; i++) {
            if (!visited[i] && scc[i] == i) {
                dfs3(i);
            }
        }

        int noin = 0, noout = 0;
        for (int i =0 ; i <= n-1; i++) {
            if (scc[i] == i) {
                 if (in[i]==0) {
                    noin++;
                }
                if (out[i]==0) {
                    noout++;
                }
            }
        }
        if (nodesInSCC.size() == 1) {
            pw.println(0);
        } else {
            pw.println(Math.max(noin, noout));
        }
    }

    static void dfs3(int node) {
        visited[node] = true;
        for (int next : condensed[node]) {
            out[node]++;
            in[next]++;
            if (!visited[next]) {
                dfs3(next);
            }
        }
    }

    static void dfs(int node) {
        visited[node] = true;
        for (int next : graph[node])
            if (!visited[next])
                dfs(next);
        
        reverseTopological.add(node);
    }

    static void dfs2(int node, int start) {
        visited[node] = true;
        scc[node] = start;
        for (int next : transposeGraph[node])
            if (!visited[next])
                dfs2(next, start);
    }
}
