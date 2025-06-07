import java.util.*;
import java.io.*;

public class RooksDefenders {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        // String[] line = br.readLine().split(" ");
        // int n = Integer.parseInt(line[0]);
        // int q = Integer.parseInt(line[1]);
        // int[] a = new int[n];
        // SegmentTree rows = new SegmentTree(a);
        // SegmentTree columns = new SegmentTree(a);
        // while (q-->0) {
        //     line = br.readLine().split(" ");
        //     if (Integer.parseInt(line[0])==1) {
        //         int r = Integer.parseInt(line[1])-1;
        //         int c = Integer.parseInt(line[2])-1;
        //         rows.update(r, 1);
        //         columns.update(c, 1);
        //     } else if (Integer.parseInt(line[0])==2) {
        //         int r = Integer.parseInt(line[1])-1;
        //         int c = Integer.parseInt(line[2])-1;
        //         rows.update(r, -1);
        //         columns.update(c, -1);
        //     } else {
        //         int r1 = Integer.parseInt(line[1])-1;
        //         int c1 = Integer.parseInt(line[2])-1;
        //         int r2 = Integer.parseInt(line[3])-1;
        //         int c2 = Integer.parseInt(line[4])-1;
        //         boolean good = rows.query(r1, r2)>=(r2-r1+1) || columns.query(c1, c2)>=(c2-c1+1);
        //         pw.println(good?"Yes":"No");
        //     }
        // }

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int q = Integer.parseInt(line[1]);
        int[] rows = new int[n+1];
        int[] columns = new int[n+1];
        TreeSet<Integer> emptyRows = new TreeSet<>(); for (int i = 1; i <= n; i++) emptyRows.add(i);
        TreeSet<Integer> emptyCols = new TreeSet<>(); for (int i = 1; i <= n; i++) emptyCols.add(i);
        while (q-->0) {
            line = br.readLine().split(" ");
            if (Integer.parseInt(line[0])==1) {
                int r = Integer.parseInt(line[1]);
                int c = Integer.parseInt(line[2]);
                rows[r]++;
                columns[c]++;
                if (emptyRows.contains(r)) emptyRows.remove(r);
                if (emptyCols.contains(c)) emptyCols.remove(c);
            } else if (Integer.parseInt(line[0])==2) {
                int r = Integer.parseInt(line[1]);
                int c = Integer.parseInt(line[2]);
                rows[r]--; if (rows[r]==0) emptyRows.add(r);
                columns[c]--; if (columns[c]==0) emptyCols.add(c);
            } else {
                int r1 = Integer.parseInt(line[1]);
                int c1 = Integer.parseInt(line[2]);
                int r2 = Integer.parseInt(line[3]);
                int c2 = Integer.parseInt(line[4]);
                // pw.println(emptyRows);
                // pw.println(emptyCols);
                boolean good = !(emptyRows.ceiling(r1)!=null && emptyRows.ceiling(r1) <= r2)
                    || !(emptyCols.ceiling(c1)!=null && emptyCols.ceiling(c1) <= c2);
                pw.println(good?"Yes":"No");
            }
        }

        br.close(); pw.close();
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

        long[] f;
        int n;

        public SegmentTree(int[] original) {
            n = original.length;
            f = new long[4*n];

            build(original, 1, 0, n-1);
        }

        public void build(int[] a, int node, int tmpL, int tmpR) {
            if (tmpL == tmpR) {
                f[node] = a[tmpL];
            } else {
                int tmpM = (tmpL + tmpR) / 2;
                build(a, 2*node, tmpL, tmpM);
                build(a, 2*node+1, tmpM+1, tmpR);
                f[node] = f[2*node] + f[2*node+1]; // computes the higher-level node afterward
            }
        }

        public long query(int l, int r, int node, int tmpL, int tmpR) {
            if (l > r)
                return 0;
            if (tmpL == l && tmpR == r)
                return f[node];
            
            int tmpM = (tmpL + tmpR) / 2; // "temporary left", "temporary right", and "temporary mid"
            return query(l, Math.min(r, tmpM), 2*node, tmpL, tmpM) +
                query(Math.max(l, tmpM+1), r, 2*node+1, tmpM+1, tmpR);
        }

        public long query(int l, int r) {
            // wrapper method
            return query(l, r, 1, 0, n-1);
        }

        public void update(int ind, int newVal, int node, int tmpL, int tmpR) {
            if (tmpL == tmpR) {
                f[node] = f[node]+newVal;
            } else {
                int tmpM = (tmpL + tmpR) / 2;
                if (ind <= tmpM)
                    update(ind, newVal, 2*node, tmpL, tmpM);
                else
                    update(ind, newVal, 2*node+1, tmpM+1, tmpR);
                f[node] = f[2*node] + f[2*node+1];
            }
        }

        public void update(int ind, int newVal) {
            update(ind, newVal, 1, 0, n-1);
        }
    }
}
