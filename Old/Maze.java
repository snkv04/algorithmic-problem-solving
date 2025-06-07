import java.util.*;
import java.io.*;

public class Maze {
    static int n, m, k;
    static char[][] maze;
    static boolean[][] visited;
    static int count = 0, count2 = 0;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        n = Integer.parseInt(line[0]);
        m = Integer.parseInt(line[1]);
        k = Integer.parseInt(line[2]);
        maze = new char[n][m];
        for (int i = 0; i <= n-1; i++) {
            maze[i] = br.readLine().toCharArray();
        }
        
        boolean found = false;
        int starti = -1, startj = -1;
        visited = new boolean[n][m];
        for (int i = 0; i <= n-1 && !found; i++) {
            for (int j = 0; j <= m-1; j++) {
                if (maze[i][j]=='.') {
                    found = true;
                    starti = i;
                    startj = j;
                    dfs(i, j);
                    break;
                }
            }
        }

        visited = new boolean[n][m];
        dfs2(starti, startj);
        for (int i = 0; i <= n-1; i++) {
            for (int j = 0; j <= m-1; j++) {
                if (maze[i][j]=='.') maze[i][j] = 'X';
                else if (maze[i][j] == 'M') maze[i][j] = '.';
            }
        }
        for (char[] row : maze) pw.println(row);

        br.close(); pw.close();
    }

    static void dfs(int i, int j) {
        if (i<0 || i >= n || j<0 || j>=m) return;
        if (visited[i][j]) return;
        if (maze[i][j] != '.') return;

        visited[i][j] = true;
        count++;

        dfs(i-1, j);
        dfs(i+1, j);
        dfs(i, j-1);
        dfs(i, j+1);
    }

    static void dfs2(int i, int j) {
        if (i<0 || i >= n || j<0 || j>=m) return;
        if (visited[i][j]) return;
        if (maze[i][j] != '.') return;
        if (count2 >= count-k) return;

        visited[i][j] = true;
        count2++;
        maze[i][j] = 'M';

        dfs2(i-1, j);
        dfs2(i+1, j);
        dfs2(i, j-1);
        dfs2(i, j+1);
    }

    // // // //

    static class Multiset {
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

    static class DSUF {
        // the "disjoint-set/union-find" data structure

        int[] parent;
        int[] size;

        public DSUF(int length) {
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
}
