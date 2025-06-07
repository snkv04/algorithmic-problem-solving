import java.util.*;
import java.io.*;

public class TheGreatRevegetation {
    static boolean[] visited;
    static ArrayList<Edge>[] adj;
    static int n, m;

    public static void main(String[] args) throws Exception {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("revegetate.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("revegetate.out")));

        String[] line = br.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        m = Integer.parseInt(line[1]);
        visited = new boolean[n];
        adj = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) {
            adj[i] = new ArrayList<Edge>();
        }
        for (int i = 1; i <= m; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[1]) - 1;
            int b = Integer.parseInt(line[2]) - 1;
            char w = line[0].charAt(0);
            adj[a].add(new Edge(b, w));
            adj[b].add(new Edge(a, w));
        }

        int components = 0;
        for (int i = 0; i <= n-1; i++) {
            if (!visited[i]) {
                components++;
                boolean works = bfs(i);
                if (!works) {
                    components = -1;
                    break;
                }
            }
        }
        if (components == -1) {
            pw.print(0);
        } else {
            pw.print(1);
            for (int i = 1; i <= components; i++) pw.print(0);
        }

        br.close(); pw.close();
    }

    static class Edge {
        int to;
        char weight;

        public Edge(int to, char weight) {
            this.to = to;
            this.weight = weight;
        }
    }

    static boolean bfs(int start) {
        Queue<Integer> q = new LinkedList<Integer>();
        int[] color = new int[n];
        q.add(start);
        color[start] = 1;
        while (!q.isEmpty()) {
            int v = q.poll();
            if (!visited[v]) {
                visited[v] = true;
                for (Edge adjacent : adj[v]) {
                    if (color[adjacent.to] == 0) {
                        q.add(adjacent.to);
                        if (adjacent.weight == 'S') color[adjacent.to] = color[v];
                        else color[adjacent.to] = 3 - color[v];
                        // System.out.println(v+" color="+color[v]+",adja weight="+adjacent.weight+",so "+adjacent.to+" color is "+color[adjacent.to]);

                    } else {
                        // the adjacent node has been visited
                        if ((adjacent.weight == 'S' && color[v] != color[adjacent.to])
                            || (adjacent.weight == 'D'  && color[v] == color[adjacent.to]))
                            return false;
                    }
                }
            }
        }

        return true;
    }
}
