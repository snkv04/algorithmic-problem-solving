import java.util.*;
import java.io.*;

public class BooksExchange {
    static int[] adj;
    static boolean[] visited;
    static int[] ans;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int q = Integer.parseInt(br.readLine());
        while (q-->0) {
            int n = Integer.parseInt(br.readLine());
            adj = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            for (int i = 0; i <= n-1; i++) adj[i]--;

            visited = new boolean[n];
            ans = new int[n];
            for (int i = 0; i <= n-1; i++) {
                if (!visited[i]) {
                    dfs(i, 0);
                }
            }
            for (int i = 0; i <= n-1; i++) pw.print(ans[i]+" ");
            pw.println();
        }

        br.close(); pw.close();
    }

    static int dfs(int node, int nodesVisited) {
        visited[node] = true;
        nodesVisited += 1;
        if (!visited[adj[node]]) {
            nodesVisited = dfs(adj[node], nodesVisited);
        }
        ans[node] = nodesVisited;
        return nodesVisited;
    }
}
