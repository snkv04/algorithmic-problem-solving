import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class MooTubeGold {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static int[] di = {0, 0, 1, -1}, dj = {1, -1, 0, 0};

    public static void main(String[] args) throws IOException {
        // br = new BufferedReader(new InputStreamReader(System.in));
        // pw = new PrintWriter(System.out);
        br = new BufferedReader(new FileReader("mootube.in"));
        pw = new PrintWriter(new BufferedWriter(new FileWriter("mootube.out")));

        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        String[] s = br.readLine().split(" ");
        int n = Integer.parseInt(s[0]), q = Integer.parseInt(s[1]);
        DSU dsu = new DSU(n);
        int[][] edges = new int[n-1][3];
        int[][] queries = new int[q][4];
        for (int i = 0; i < n-1; ++i) {
            s = br.readLine().split(" ");
            edges[i][0] = Integer.parseInt(s[0])-1;
            edges[i][1] = Integer.parseInt(s[1])-1;
            edges[i][2] = Integer.parseInt(s[2]);
        }
        Arrays.sort(edges, Comparator.comparingInt(o -> o[2]));

        for (int i = 0; i < q; ++i) {
            s = br.readLine().split(" ");
            queries[i][0] = i;
            queries[i][1] = Integer.parseInt(s[0]);
            queries[i][2] = Integer.parseInt(s[1]) - 1;
        }
        Arrays.sort(queries, Comparator.comparingInt(o -> o[1]));

        int j = n-2;
        for (int i = q-1; i >= 0; --i) {
            int k = queries[i][1], v = queries[i][2];
            while (j >= 0 && edges[j][2] >= k) {
                dsu.union(edges[j][0], edges[j][1]);
                --j;
            }
            queries[i][3] = dsu.size(v) - 1;
        }
        Arrays.sort(queries, Comparator.comparingInt(o -> o[0]));

        for (int i = 0; i < q; ++i) {
            pw.println(queries[i][3]);
        }
    }

    static class DSU {
        // disjoint-set/union-find data structure
        int[] parent;
        int[] size;

        public DSU(int length) {
            parent = new int[length];
            size = new int[length];
            for (int i = 0; i <= length - 1; i++) parent[i] = i;
            Arrays.fill(size, 1);
        }

        public int find(int x) {
            if (parent[x] == x) return x;
            else {
                parent[x] = find(parent[x]);
                return parent[x];
            }
        }

        public void union(int a, int b) {
            int c = find(a);
            int d = find(b);
            if (c != d) {
                int sum = size[c] + size[d];
                parent[d] = c;
                size[c] = sum;
                size[d] = sum;
            }
        }

        public int size(int x) {
            return size[find(x)];
        }
    }

}
