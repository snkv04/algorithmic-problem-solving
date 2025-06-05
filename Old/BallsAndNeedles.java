import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class BallsAndNeedles {
    static BufferedReader br;
    static PrintWriter pw;
    static HashMap<String, Integer> toNum3D;
    static HashMap<String, Integer> toNum2D;

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
        int k = Integer.parseInt(br.readLine());
        String[] input = new String[k];
        for (int i = 0; i <= k-1; i++) {
            input[i] = br.readLine();
        }

        toNum3D = new HashMap<>();
        int count = 0;
        for (int i = 0; i <= k-1; i++) {
            String[] split = input[i].split(" ");
            String p1 = split[0]+" "+split[1]+" "+split[2], p2 = split[3]+" "+split[4]+" "+split[5];
            if (!toNum3D.containsKey(p1)) {
                toNum3D.put(p1, count++);
            }
            if (!toNum3D.containsKey(p2)) {
                toNum3D.put(p2, count++);
            }
        }

        DSU dsu = new DSU(count);
        boolean trueChain = false;
        HashSet<String> edges = new HashSet<String>();
        for (int i = 0; i <= k-1; i++) {
            String[] split = input[i].split(" ");
            int p1 = toNum3D.get(split[0]+" "+split[1]+" "+split[2]),
                p2 = toNum3D.get(split[3]+" "+split[4]+" "+split[5]);
            if (edges.contains(Math.min(p1, p2)+""+Math.max(p1, p2))) {
                continue; // duplicate edge
            }
            if (dsu.find(p1) == dsu.find(p2) && p1 != p2) {
                trueChain = true;
                break;
            }
            dsu.union(p1, p2);
            edges.add(Math.min(p1, p2)+""+Math.max(p1, p2));
        }

        toNum2D = new HashMap<>();
        count = 0;
        for (int i = 0; i <= k-1; i++) {
            String[] split = input[i].split(" ");
            String p1 = split[0]+" "+split[1], p2 = split[3]+" "+split[4];
            if (!toNum2D.containsKey(p1)) {
                toNum2D.put(p1, count++);
            }
            if (!toNum2D.containsKey(p2)) {
                toNum2D.put(p2, count++);
            }
        }

        DSU dsu2 = new DSU(count);
        boolean floorChain = false;
        edges = new HashSet<String>();
        for (int i = 0; i <= k-1; i++) {
            String[] split = input[i].split(" ");
            int p1 = toNum2D.get(split[0]+" "+split[1]),
                p2 = toNum2D.get(split[3]+" "+split[4]);
            if (edges.contains(Math.min(p1, p2)+""+Math.max(p1, p2))) {
                continue; // duplicate edge
            }
            if (dsu2.find(p1) == dsu2.find(p2) && p1 != p2) {
                floorChain = true;
                break;
            }
            dsu2.union(p1, p2);
            edges.add(Math.min(p1, p2)+""+Math.max(p1, p2));
        }

        pw.println(trueChain?"True closed chains":"No true closed chains");
        pw.println(floorChain?"Floor closed chains":"No floor closed chains");
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
            return size[x];
        }
    }
}
