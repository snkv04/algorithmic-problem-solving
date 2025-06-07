import java.util.*;
import java.io.*;

public class Moocast {
    static ArrayList<Integer>[] adj;
    static boolean[] visited;
    static int count;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("moocast.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("moocast.out")));
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[] xs = new int[n];
        int[] ys = new int[n];
        int[] ps = new int[n];
        for (int i = 0; i <= n-1; i++) {
            String[] line = br.readLine().split(" ");
            xs[i] = Integer.parseInt(line[0]);
            ys[i] = Integer.parseInt(line[1]);
            ps[i] = Integer.parseInt(line[2]);
        }
        adj = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) {
            adj[i] = new ArrayList<Integer>();
        }
        for (int i = 0; i <= n-1; i++) {
            for (int j = 0; j <= n-1; j++) {
                if (j != i && Math.pow(ps[i], 2) >= (Math.pow(xs[i]-xs[j], 2) + Math.pow(ys[i]-ys[j], 2))) {
                    adj[i].add(j);
                }
            }
        }

        int max = 0;
        for (int i = 0; i <= n-1; i++) {
            count = 0;
            visited = new boolean[n];
            dfs(i);
            if (count > max) max = count;
        }
        pw.println(max);

        br.close(); pw.close();
    }

    // public static void dfs(int node) {
    //     visited[node] = true;
    //     count++;
    //     for (int adjacentNode : adj[node]) {
    //         if (!visited[adjacentNode]) {
    //             dfs(adjacentNode);
    //         }
    //     }
    // }

    // just practicing with iterative implementation
    public static void dfs(int node) {
        Stack<Integer> stack = new Stack<Integer>();
        stack.push(node);
        while(!stack.isEmpty()) {
            int curr = stack.pop();
            if (!visited[curr]) {
                visited[curr] = true;
                count++;
                for (int adjacentNodeToCurr : adj[curr]) {
                    if (!visited[adjacentNodeToCurr]) {
                        stack.push(adjacentNodeToCurr);
                    }
                }
            }
        }
    }
}
