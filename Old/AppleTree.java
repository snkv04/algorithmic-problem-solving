import java.util.*;
import java.io.*;

public class AppleTree {
    static ArrayList<Integer>[] adjLists;
    static boolean[] visited;
    static int[] numLeaves;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            adjLists = new ArrayList[n];
            for (int j=0; j<=n-1; j++) adjLists[j] = new ArrayList<Integer>();

            for (int j = 1; j <= n-1; j++) {
                String[] line = br.readLine().split(" ");
                int a = Integer.parseInt(line[0])-1;
                int b = Integer.parseInt(line[1]) - 1;
                adjLists[a].add(b);
                adjLists[b].add(a);
            }

            visited = new boolean[n];
            numLeaves = new int[n];
            dfs(0);
            // pw.println(Arrays.toString(numLeaves));

            int q = Integer.parseInt(br.readLine());
            for (int j = 1; j <= q; j++) {
                String[] line = br.readLine().split(" ");
                int a = Integer.parseInt(line[0])-1;
                int b = Integer.parseInt(line[1]) - 1;
                pw.println((long) numLeaves[a] * numLeaves[b]);
            }
        }

        br.close(); pw.close();
    }

    static void dfs(int node) {
        int leaves = 0;
        visited[node] = true;
        for (int next : adjLists[node]) {
            if (!visited[next]) {
                dfs(next);
                leaves += numLeaves[next];
            }
        }
        if (leaves == 0) numLeaves[node] = 1;
        else numLeaves[node] = leaves;
    }
}
