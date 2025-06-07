import java.util.*;
import java.io.*;

public class RoadToSavings {
    static BufferedReader br;
    static PrintWriter pw;
    static ArrayList<Pair>[] adj;

    public static void main(String[] args) throws IOException {

        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        solve();

        br.close();
        pw.close();
    }

    public static void solve() throws IOException {
        String[] s = br.readLine().split(" ");
        int n = Integer.parseInt(s[0]), m = Integer.parseInt(s[1]), a = Integer.parseInt(s[2]), b = Integer.parseInt(s[3]);
        a--; b--;
        adj = new ArrayList[n]; for (int i = 0; i < n; i++) adj[i] = new ArrayList<Pair>();
        int[][] edges = new int[m][3];
        for (int i = 0; i < m; i++) {
            edges[i] = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            edges[i][0]--;
            edges[i][1]--;
            adj[edges[i][0]].add(new Pair(edges[i][1], edges[i][2])); // new Pair(to, weight)
            adj[edges[i][1]].add(new Pair(edges[i][0], edges[i][2]));
        }

        int[] dista = new int[n], distb = new int[n];
        Arrays.fill(dista, (int) 1e9); Arrays.fill(distb, (int) 1e9);
        dista[a] = 0;
        distb[b] = 0;
        
        PriorityQueue<Pair> pq = new PriorityQueue<Pair>(Comparator.comparingInt(o -> o.b)); // Pair(node, dist)
        pq.add(new Pair(a, 0));
        while (!pq.isEmpty()) {
            Pair p = pq.poll();
            int node = p.a;
            int nodeDist = p.b;
            if (nodeDist > dista[node]) {
                continue;
            }

            for (Pair next : adj[node]) {
                int to = next.a, weight = next.b;
                if (dista[to] > nodeDist + weight) {
                    dista[to] = nodeDist + weight;
                    pq.add(new Pair(to, dista[to]));
                }
            }
        }
        
        pq = new PriorityQueue<Pair>(Comparator.comparingInt(o -> o.b)); // Pair(node, dist)
        pq.add(new Pair(b, 0));
        while (!pq.isEmpty()) {
            Pair p = pq.poll();
            int node = p.a;
            int nodeDist = p.b;
            if (nodeDist > distb[node]) {
                continue;
            }

            for (Pair next : adj[node]) {
                int to = next.a, weight = next.b;
                if (distb[to] > nodeDist + weight) {
                    distb[to] = nodeDist + weight;
                    pq.add(new Pair(to, distb[to]));
                }
            }
        }
        // pw.println(Arrays.toString(dista));
        // pw.println(Arrays.toString(distb));

        int sum = 0;
        for (int i = 0; i < m; i++) {
            int f = edges[i][0], t = edges[i][1], w = edges[i][2];
            sum += w;
            if (dista[f] + distb[t] + w == dista[b] || dista[t] + distb[f] + w == dista[b]) {
                sum -= w;
            }
        }
        pw.println(sum);
    }

    static class Pair {
        int a, b;

        public Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }
}