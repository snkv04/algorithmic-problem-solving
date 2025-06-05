import java.util.*;
import java.io.*;

public class CandyPartyNew {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static int[] di = {0, 0, 1, -1}, dj = {1, -1, 0, 0};
    static HashMap<Long, Pair> make;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        make = new HashMap<>();
        for (int i = 0; i <= 31; i++) {
            for (int j = 0; j <= 31; j++) {
                long a = ((long) 1) << i;
                long b = ((long) 1) << j;
                make.put(a - b, new Pair(i, j));
                // make.put(b - a, new Pair(b, a));
            }
        }
        // pw.println(make);

        int t = Integer.parseInt(br.readLine()); // 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        int n = Integer.parseInt(br.readLine());
        long[] a = Arrays.stream(br.readLine().split(" ")).mapToLong(Integer::parseInt).toArray();
        long sum = 0;
        for (long num : a) sum += num;
        if (sum % n != 0) {
            pw.println("no");
            return;
        }
        sum /= n;

        Multiset add = new Multiset(), subtract = new Multiset();
        for (long num : a) {
            long diff = sum - num;
            if (!make.containsKey(diff)) {
                pw.println("no");
                // pw.println("here");
                return;
            }
            Pair p = make.get(diff);
            add.add(p.a); subtract.add(p.b);
        }

        boolean works = true;
        if (add.mset.size() != subtract.mset.size()) {
            works = false;
        }
        for (Map.Entry<Long, Integer> entry : add.mset.entrySet()) {
            if (!subtract.mset.containsKey(entry.getKey()) || !subtract.mset.get(entry.getKey()).equals(entry.getValue())) {
                works = false;
                break;
            }
        }
        pw.println(works?"yes":"no");
    }

    // // // //

    static class Multiset { // ordered multiset
        TreeMap<Long, Integer> mset = new TreeMap<>();

        public void add(long x) {
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + 1);
            } else {
                mset.put(x, 1);
            }
        }
        
        public void remove(long x) {
            mset.put(x, mset.get(x) - 1);
            if (mset.get(x) == 0) mset.remove(x);
        }

        public void add(long x, int q) {
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

    static long gcd(long a, long b) {
        long B = Math.min(a, b);
        long A = Math.max(a, b);
        while (B != 0) {
            long temp = B;
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
        int n;
        long[] t;
        // long[] lzAdd;
        // long[] lzSet;
        // boolean[] marked;

        public SegmentTree(int[] original) {
            n = original.length;
            t = new long[4*n];
            // lzAdd = new long[4*n];
            // lzSet = new long[4*n];
            // marked = new boolean[4*n]; // marked [i] = whether tree[i] should be set to lzSet[i]

            build(original, 1, 0, n-1);
        }

        public void build(int[] a, int vertex, int vl, int vr) {
            if (vl == vr) {
                t[vertex] = a[vl];
            } else {
                int vm = (vl + vr) / 2;
                build(a, 2*vertex, vl, vm);
                build(a, 2*vertex+1, vm+1, vr);
                t[vertex] = Math.max(t[2*vertex], t[2*vertex+1]); // computes the higher-level node afterward
            }
        }

        public long query(int l, int r, int vertex, int vl, int vr) {
            if (l > r)
                return Long.MIN_VALUE / 2;
            if (vl == l && vr == r)
                return t[vertex];
            
            int vm = (vl + vr) / 2; // "vertex's left", "vertex's right", and "vertex's middle"
            return Math.max(
                query(l, Math.min(r, vm), 2*vertex, vl, vm),
                query(Math.max(l, vm+1), r, 2*vertex+1, vm+1, vr)
            );
        }

        public long query(int l, int r) {
            // wrapper method
            return query(l, r, 1, 0, n-1);
        }

        public void update(int ind, int newVal, int vertex, int vl, int vr) {
            if (vl == vr) {
                t[vertex] = newVal;
            } else {
                int vm = (vl + vr) / 2;
                if (ind <= vm)
                    update(ind, newVal, 2*vertex, vl, vm);
                else
                    update(ind, newVal, 2*vertex+1, vm+1, vr);
                t[vertex] = Math.max(t[2*vertex], t[2*vertex+1]);
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
        int i, j;

        public Point(int i, int j) {
            this.i = i;
            this.j = j;
        }

        // int x, y;

        // public Point(int x, int y) {
        //     this.x = x;
        //     this.y = y;
        // }
    }

    static class DSU2 {
        // 2-dimensional DSU
        // this may or may not be useless since a 2D array can just be mapped to a 1D array :/
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

    static long taxiDist(long x1, long y1, long x2, long y2) {
        // Manhattan distance between two points in the Cartesian coordinate plane
        return Math.abs(x2 - x1) + Math.abs(y2 - y1);
    }

    static double dist(long x1, long y1, long x2, long y2) {
        // uses the Pythagorean theorem to calculate the distance between two points
        // in the Cartesian coordinate plane
        long a = x2 - x1;
        long b = y2 - y1;
        return Math.sqrt(Math.pow(a, 2) + Math.pow(b, 2));
        // return (long) (Math.pow(a, 2) + Math.pow(b, 2)); // to return squared distance
    }

    static <T> void generatePermutations(int k, T[] a) {
        if (k == 1) {
            System.out.println(Arrays.toString(a)); // change this to whatever is considered as outputting the permutation
        } else {
            generatePermutations(k-1, a);
            for (int i = 0; i <= k-2; i++) {
                if (k % 2 == 0) {
                    T temp = a[i];
                    a[i] = a[k-1];
                    a[k-1] = temp;
                } else {
                    T temp = a[0];
                    a[0] = a[k-1];
                    a[k-1] = temp;
                }
                generatePermutations(k-1, a);
            }
        }
    }

    static class Pair {
        long a, b;

        public Pair(long a, long b) {
            this.a = a;
            this.b = b;
        }
        
        @Override
        public boolean equals(Object obj) {
            if (this == obj) return true;
            if (obj == null) return false;
            if (!(obj instanceof Pair)) return false;

            Pair other = (Pair) obj;
            return this.a == other.a && this.b == other.b;
        }

        @Override
        public int hashCode() {
            return (this.a+" "+this.b).hashCode();
        }

        public String toString() {
            return "(a="+a+", b="+b+")";
        }
    }

    // runs the Extended Euclidean Algorithm on inputs a and b,
    // and returns a length-3 array in the form [g, x, y]
    // such that g = gcd(a, b) = ax + by
    static long[] bezouts(long a, long b) {
        if (b == 0) {
            return new long[] {a, 1, 0}; // in the last step of the EA, gcd = a, so x = 1 and y = 0
        }

        long q = a / b, r = a % b; // a = bq + r, where 0 <= r < b
        long[] result = bezouts(b, r); // the "x" and "y" here are from the next step of the EA
        long gcd = result[0], x = result[1], y = result[2]; // gcd = bx + ry
        return new long[] {gcd, y, x - y * q}; // r = a - bq --> gcd = ay + b(x - yq) --> (x, y) := (y, x - yq)
    }
}
