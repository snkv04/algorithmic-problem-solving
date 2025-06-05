import java.util.*;
import java.io.*;

public class Cowntagion {
    static ArrayList<Integer>[] adj;
    static boolean[] visited;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        adj = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) adj[i]=new ArrayList<Integer>();
        for (int i = 1; i <= n-1; i++) {
            String[] line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0])-1;
            int b = Integer.parseInt(line[1])-1;
            adj[a].add(b);
            adj[b].add(a);
        }

        visited = new boolean[n];
        Queue<Integer> q = new LinkedList<>();
        q.add(0);
        int ans = 0;
        while (!q.isEmpty()) {
            int farm = q.poll();
            if (!visited[farm]) {
                visited[farm] = true;
                int unvisitedAdj = 0;
                for (int adjacent : adj[farm]) {
                    if (!visited[adjacent]) {
                        q.add(adjacent);
                        unvisitedAdj++;
                        ans++;
                    }
                }
                if (unvisitedAdj != 0) {
                    int need = unvisitedAdj + 1;
                    int power = 0;
                    int val = 1;
                    while (val < need) {
                        val*=2;
                        power++;
                    }
                    ans += power;
                }
            }
        }
        pw.println(ans);

        br.close(); pw.close();
    }
}
