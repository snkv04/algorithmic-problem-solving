import java.util.*;
import java.io.*;

public class Bumped {
    static int n, m, f, s, t;
    static ArrayList<Edge>[] adjRoads;
    static Edge2[] flights;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        m = Integer.parseInt(line[1]);
        f = Integer.parseInt(line[2]);
        s = Integer.parseInt(line[3]);
        t = Integer.parseInt(line[4]);
        adjRoads = new ArrayList[n];
        for (int i = 0; i <= n-1; i++) adjRoads[i] = new ArrayList<>();
        while (m-- > 0) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]);
            int b = Integer.parseInt(line[1]);
            int c = Integer.parseInt(line[2]);
            adjRoads[a].add(new Edge(b, c));
            adjRoads[b].add(new Edge(a, c));
        }
        flights = new Edge2[f];
        while (f-->0) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]);
            int b = Integer.parseInt(line[1]);
            flights[f] = new Edge2(a, b);
        }

        long[] distFromS = new long[n]; for (int i = 0; i <= n-1; i++) if (i != s) distFromS[i] = Long.MAX_VALUE / 2;
        long[] distFromT = new long[n]; for (int i = 0; i <= n-1; i++) if (i != t) distFromT[i] = Long.MAX_VALUE / 2;
        // pw.println(Arrays.toString(distFromS)); pw.println(Arrays.toString(distFromT));
        PriorityQueue<Pair> pq = new PriorityQueue<Pair>(Comparator.comparingLong(o -> o.b));
        pq.add(new Pair(s, 0));
        while (!pq.isEmpty()) {
            Pair p = pq.poll();
            if (distFromS[p.a] < p.b) continue;
            for (Edge next : adjRoads[p.a]) {
                if (distFromS[p.a] + next.weight < distFromS[next.to]) {
                    distFromS[next.to] = distFromS[p.a] + next.weight;
                    pq.add(new Pair(next.to, distFromS[next.to]));
                }
            }
        }
        // pq = new PriorityQueue<>(Comparator.comparingLong(o -> distFromT[o]));
        // pq = new PriorityQueue<Pair>(Comparator.comparingLong(o -> o.b));
        // pq.clear();
        pq.add(new Pair(t, 0));
        while (!pq.isEmpty()) {
            Pair p = pq.poll();
            int node = p.a;
            if (distFromT[p.a] < p.b) continue;
            for (Edge next : adjRoads[node]) {
                if (distFromT[node] + next.weight < distFromT[next.to]) {
                    distFromT[next.to] = distFromT[node] + next.weight;
                    pq.add(new Pair(next.to, distFromT[next.to]));
                }
            }
        }

        long min = distFromS[t];
        for (Edge2 flight : flights) {
            min = Math.min(min, distFromS[flight.a] + distFromT[flight.b]);
        }
        pw.println(min);

        br.close(); pw.close();
    }

    static class Edge {
        int to, weight;

        public Edge(int b, int w) {
            this.to = b;
            this.weight = w;
        }
    }

    static class Edge2 {
        int a, b;

        public Edge2(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }

    // // // //

    static class Multiset { // ordered multiset
        TreeMap<Integer, Integer> mset = new TreeMap<>();

        public void add(int x) {
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + 1);
            } else {
                mset.put(x, 1);
            }
        }
        
        public void remove(int x) {
            mset.put(x, mset.get(x) - 1);
            if (mset.get(x) == 0) mset.remove(x);
        }

        public void add(int x, int q) {
            // q for quantity
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + q);
            } else {
                mset.put(x, q);
            }
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
            return size[x];
        }
    }

    static int gcd(int a, int b) {
        int B = Math.min(a, b);
        int A = Math.max(a, b);
        while (B != 0) {
            int temp = B;
            B = A % B;
            A = temp;
        }
        return A;
    }

    static ArrayList<Integer> primeFactorization(int n) {
        ArrayList<Integer> factors = new ArrayList<Integer>();
        for (int i = 2; i <= Math.sqrt(n); i++) {
            while (n % i == 0) {
                n /= i;
                factors.add(i);
            }
        }
        if (n != 1) {
            factors.add(n);
        }
        return factors;
    }

    static class SegmentTree {
        // this implementation is for doing range maximum queries by default
        // it's written recursively for now :|
        int[] f;
        int n;

        public SegmentTree(int[] original) {
            n = original.length;
            f = new int[4*n];

            build(original, 1, 0, n-1);
        }

        public void build(int[] a, int node, int tmpL, int tmpR) {
            if (tmpL == tmpR) {
                f[node] = a[tmpL];
            } else {
                int tmpM = (tmpL + tmpR) / 2;
                build(a, 2*node, tmpL, tmpM);
                build(a, 2*node+1, tmpM+1, tmpR);
                f[node] = Math.max(f[2*node], f[2*node+1]); // computes the higher-level node afterward
            }
        }

        public int query(int l, int r, int node, int tmpL, int tmpR) {
            if (l > r)
                return Integer.MIN_VALUE;
            if (tmpL == l && tmpR == r)
                return f[node];
            
            int tmpM = (tmpL + tmpR) / 2; // "temporary left", "temporary right", and "temporary mid"
            return Math.max(
                query(l, Math.min(r, tmpM), 2*node, tmpL, tmpM),
                query(Math.max(l, tmpM+1), r, 2*node+1, tmpM+1, tmpR)
            );
        }

        public int query(int l, int r) {
            // wrapper method
            return query(l, r, 1, 0, n-1);
        }

        public void update(int ind, int newVal, int node, int tmpL, int tmpR) {
            if (tmpL == tmpR) {
                f[node] = newVal;
            } else {
                int tmpM = (tmpL + tmpR) / 2;
                if (ind <= tmpM)
                    update(ind, newVal, 2*node, tmpL, tmpM);
                else
                    update(ind, newVal, 2*node+1, tmpM+1, tmpR);
                f[node] = Math.max(f[2*node], f[2*node+1]);
            }
        }

        public void update(int ind, int newVal) {
            update(ind, newVal, 1, 0, n-1);
        }
    }

    static long sqrt(long n) {
        // calculates the floor of sqrt(n) in O(log(n))
        if (n == 0) return 0;
        else if (n < 0) throw new IllegalArgumentException("can't return imaginary numbers");
        long l = 1, r = n, sqrt = -1;
        while (l <= r) {
            long mid = (l + r) / 2;
            long factor = n / mid;
            if (mid <= factor) {
                sqrt = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return sqrt;
    }

    static class Point {
        // can change to xy system if needed
        // when would i need both coordinate systems?
        int i, j;

        public Point(int i, int j) {
            this.i = i;
            this.j = j;
        }
    }

    static class DSU2 {
        // 2-dimensional DSU
        Point[][] parent;
        int[][] size;

        public DSU2(int r, int c) {
            parent = new Point[r][c];
            size = new int[r][c];
            for (int i = 0; i <= r-1; i++) {
                for (int j = 0; j <= c-1; j++) {
                    parent[i][j] = new Point(i, j);
                }
            }
            for (int i = 0; i <= r-1; i++) {
                Arrays.fill(size[i], 1);
            }
        }

        public Point find(int i, int j) {
            if (parent[i][j].i == i && parent[i][j].j==j) {
                return parent[i][j];
            } else {
                parent[i][j] = find(parent[i][j].i, parent[i][j].j);
                return parent[i][j];
            }
        }

        public void union(int ai, int aj, int bi, int bj) {
            Point c = find(ai, aj);
            Point d = find(bi, bj);
            if (c.i != d.i || c.j != d.j) {
                int sum = size[c.i][c.j] + size[d.i][d.j];
                parent[d.i][d.j] = c;
                size[c.i][c.j] = sum;
                size[d.i][d.j] = sum;
            }
        }

        public int size(int i, int j) {
            return size[i][j];
        }
    }

    static class Pair {
        int a;
        long b;

        public Pair(int a, long b) {
            this.a = a;
            this.b = b;
        }
    }
}
