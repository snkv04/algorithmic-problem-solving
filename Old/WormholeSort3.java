import java.util.*;
import java.io.*;

public class WormholeSort3 {
    static int n;
    static int m;
    static ArrayList<Edge> edgeList;
    static int[] p;
    static int[] parent;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new FileReader("wormsort.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("wormsort.out")));

        String[] line = br.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        m = Integer.parseInt(line[1]);
        p = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        edgeList = new ArrayList<Edge>();
        for (int i = 0; i <= n-1; i++) {
            // decrements the values of the permutation array
            p[i] = p[i] - 1;
        }
        for (int i = 1; i <= m; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]) - 1;
            int b = Integer.parseInt(line[1]) - 1;
            int w = Integer.parseInt(line[2]);
            edgeList.add(new Edge(a, b, w));
        }
        edgeList.sort(new Comp());
        // edge list is now sorted in reverse order of edge weights

        parent = new int[n];
        for (int i=0; i<=n-1; i++) parent[i] = i;
        if (check()) pw.println(-1);
        else {
            int answer = Integer.MAX_VALUE;
            for (int i = 0; i <= m-1; i++) {
                Edge e = edgeList.get(i);
                answer = e.weight;
                union(e.from, e.to);

                if (check()) {
                    break;
                }
            }
            pw.println(answer);
        }

        br.close(); pw.close();
    }

    static class Edge {
        int from, to, weight;

        public Edge(int from, int to, int weight) {
            this.from = from;
            this.to = to;
            this.weight = weight;
        }
    }

    static class Comp implements Comparator<Edge> {
        public int compare(Edge e1, Edge e2) {
            return -Integer.compare(e1.weight, e2.weight);
        }
    }

    static boolean check() {
        // checks if each cow is in the same connected component, where every edge
        // has weight >= mid, as its proper location
        for (int i = 0; i<=n-1; i++) {
            if (find(i) != find(p[i])) return false;
        }
        return true;
    }

    static int find(int a) {
        if (parent[a] == a) return a;
        else {
            parent[a] = find(parent[a]);
            return parent[a];
        }
    }
    
    static void union(int a, int b) {
        int c = parent[a];
        int d = parent[b];
        if (c != d) {
            parent[d] = c;
        }
    }
}
