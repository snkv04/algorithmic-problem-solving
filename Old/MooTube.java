import java.util.*;
import java.io.*;

public class MooTube {
    static ArrayList<Edge>[] adj;
    static int  count = -1;
    static boolean[] visited;

    @SuppressWarnings("unchecked")
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("mootube.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("mootube.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int q = Integer.parseInt(line[1]);
        adj = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) {
            adj[i] = new ArrayList<Edge>();
        }
        for (int i = 1; i <= n-1; i++) {
            String[] edgeLine = br.readLine().split(" ");
            int a = Integer.parseInt(edgeLine[0]) - 1;
            int b = Integer.parseInt(edgeLine[1]) - 1;
            int w = Integer.parseInt(edgeLine[2]);
            adj[a].add(new Edge(b, w));
            adj[b].add(new Edge(a, w));
        }

        for (int i = 1; i <= q; i++) {
            String[] queryLine = br.readLine().split(" ");
            int k = Integer.parseInt(queryLine[0]);
            int v = Integer.parseInt(queryLine[1]) - 1;
            count = -1;
            visited = new boolean[n];
            dfs(v, k);
            pw.println(count);
        }

        br.close(); pw.close();
    }

    // only visits nodes if the edge to that node is higher than k
    // returns how many nodes were visited
    public static void dfs(int start, int k) {
        count++;
        visited[start] = true;
        for (Edge adjacentNode : adj[start]) {
            if (!visited[adjacentNode.to] && adjacentNode.weight >= k) {
                dfs(adjacentNode.to, k);
            }
        }
    }

    static class Edge {
        int to;
        int weight;

        public Edge(int to, int weight) {
            this.to = to;
            this.weight = weight;
        }
    }
}
