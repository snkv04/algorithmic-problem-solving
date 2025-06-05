import java.util.*;
import java.io.*;

public class BuildDependencies {
    static BufferedReader br;
    static PrintWriter pw;
    static ArrayList<Integer>[] adj;
    static boolean[] visited;
    static HashMap<String, Integer> toNum;
    static ArrayList<String> toStr;
    static Deque<Integer> reverse;

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
        int n = Integer.parseInt(br.readLine());
        String[][] input = new String[n][0];
        toNum = new HashMap<>();
        toStr = new ArrayList<>();
        for (int i = 0; i <= n-1; i++) {
            input[i] = br.readLine().split(" ");
            input[i][0] = input[i][0].substring(0, input[i][0].length()-1);
            toNum.put(input[i][0], i);
            toStr.add(input[i][0]);
        }

        adj = new ArrayList[n];
        for (int i =0 ; i <= n-1; i++) adj[i] = new ArrayList<>();
        for (int i = 0; i <= n-1; i++) {
            for (int j = 1; j <= input[i].length-1; j++) {
                adj[toNum.get(input[i][j])].add(toNum.get(input[i][0]));
            }
        }

        visited = new boolean[n];
        reverse = new LinkedList<>();
        dfs(toNum.get(br.readLine()));

        while (!reverse.isEmpty()) {
            pw.println(toStr.get(reverse.pollLast()));
        }
    }

    static void dfs(int node) {
        visited[node] = true;
        for (int next : adj[node]) {
            if (!visited[next]) {
                dfs(next);
            }
        }
        reverse.add(node);
    }
}
