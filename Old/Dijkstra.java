import java.util.*;
import java.io.*;

public class Dijkstra {
    static ArrayList<Edge>[] adjLists;
    static long[] dist;
    static int[] prev;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int m = Integer.parseInt(line[1]);
        adjLists = new ArrayList[n+1];
        for (int i = 1; i <= n; i++) adjLists[i] = new ArrayList();
        for (int i = 1; i <= m; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]);
            int b = Integer.parseInt(line[1]);
            int w = Integer.parseInt(line[2]);
            adjLists[a].add(new Edge(b, w));
            adjLists[b].add(new Edge(a, w));
        }

        dist = new long[n+1];
        dist[1] = 0;
        for (int i = 2; i <= n; i++) dist[i] = Long.MAX_VALUE / 2;
        PriorityQueue<Integer> pq = new PriorityQueue<Integer>(Comparator.comparingLong(o -> dist[o]));
        pq.add(1);
        int[] prev = new int[n+1];
        prev[1] = 1;
        while (!pq.isEmpty()) {
            int node = pq.poll();
            for (Edge next : adjLists[node]) {
                if (dist[next.to] > dist[node] + next.weight) {
                    dist[next.to] = dist[node] + next.weight;
                    prev[next.to] = node;
                    pq.add(next.to);
                }
            }
        }

        Stack<Integer> path = new Stack<Integer>();
        path.add(n);
        int start = n;
        while (start != 1 && start != 0) {
            path.add(prev[start]);
            start = prev[start];
        }
        if (path.peek() != 1) pw.print(-1);
        else while (!path.isEmpty()) pw.print(path.pop() + " ");

        br.close(); pw.close();
    }

    static class Edge {
        int to;
        long weight;

        public Edge(int to, int weight) {
            this.to = to;
            this.weight = weight;
        }
    }
}
