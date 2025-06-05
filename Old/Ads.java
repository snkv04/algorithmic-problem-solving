import java.util.*;
import java.io.*;

public class Ads {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static char[][] grid;
    static HashSet<Point> border;
    static boolean[][] visited;
    static int rows, cols;
    static TreeSet<Box> boxesByLeft, boxesByTop;

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
        String[] inp = br.readLine().split(" ");
        rows = Integer.parseInt(inp[0]); cols = Integer.parseInt(inp[1]);
        grid = new char[rows][cols];
        for (int i = 0; i < rows; i++) {
            grid[i] = br.readLine().toCharArray();
            // pw.println("|"+String.valueOf(grid[i])+"|");
        }

        visited = new boolean[rows][cols];
        boxesByLeft = new TreeSet<>(new ByLeft());
        boxesByTop = new TreeSet<>(new ByTop());
        for (int i = 0; i <= rows-1; i++) {
            for (int j = 0; j <= cols-1; j++) {
                if (grid[i][j] == '+' && !visited[i][j]) {
                    border = new HashSet<>();
                    dfs(i, j);

                    int top = 200, left = 200, right = -1, bottom = -1;
                    for (Point p : border) {
                        top = Math.min(top, p.i);
                        left = Math.min(left, p.j);
                        right = Math.max(right, p.j);
                        bottom = Math.max(bottom, p.i);
                    }
                    boxesByLeft.add(new Box(top, bottom, left, right));
                    boxesByTop.add(new Box(top, bottom, left, right));
                }
            }
        }
        // for (Point box : boxesByLeft) pw.println("top row is "+box.i+", leftmost col is "+box.j);

        visited = new boolean[rows][cols];
        char[] _allowed = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM?!,. +".toCharArray();
        HashSet<Character> allowed = new HashSet<>(); for (char c : _allowed) allowed.add(c);
        for (int i = 0; i <= rows-1; i++) {
            for (int j = 0; j <= cols-1; j++) {
                if (!visited[i][j] && !allowed.contains(grid[i][j])) {
                    // System.out.println("not allowed character at i="+i+", j="+j);
                    int top = boxesByTop.lower(new Box(i, -1, j, -1)).top;
                    int left = boxesByLeft.lower(new Box(i, -1, j, -1)).left;
                    Box box = boxesByLeft.floor(new Box(top, -1, left, -1));
                    boxesByLeft.remove(box);
                    boxesByTop.remove(box);
                    
                    for (int k = box.top; k <= box.bottom; k++) {
                        for (int l = box.left; l <= box.right; l++) {
                            visited[k][l] = true;
                            grid[k][l] = ' ';
                        }
                    }
                    j = box.right;
                }
            }
        }

        for (int i = 0; i <= rows-1; i++) {
            // pw.print("|");
            for (int j =0 ; j <= cols-1; j++) {
                pw.print(grid[i][j]);
            }
            // pw.println("|");
            pw.println();
        }
    }

    static void dfs(int i, int j) {
        if (i<0 || i>=rows || j<0 || j>=cols) return;
        if (visited[i][j]) return;
        if (grid[i][j] != '+') return;

        visited[i][j] = true;
        border.add(new Point(i, j));
        dfs(i, j+1); dfs(i, j-1); dfs(i+1, j); dfs(i-1, j);
    }

    static class ByTop implements Comparator<Box> {
        public int compare(Box b1, Box b2) {
            if (b1.top != b2.top) return Integer.compare(b1.top, b2.top);
            else return Integer.compare(b1.left, b2.left);
        }
    }

    static class ByLeft implements Comparator<Box> {
        public int compare(Box b1, Box b2) {
            if (b1.left != b2.left) return Integer.compare(b1.left, b2.left);
            else return Integer.compare(b1.top, b2.top);
        }
    }

    static class Box {
        int top, bottom, left, right;

        public Box(int top, int bottom, int left, int right) {
            this.top = top;
            this.bottom = bottom;
            this.left = left;
            this.right = right;
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
        int a, b;

        public Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }
}
