import java.util.*;
import java.io.*;

public class RATS {
    static int MOD = (int) (1e9 + 7); // 998244353

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int P = Integer.parseInt(br.readLine());
        for (int p = 1; p <= P; p++) {
            String[] line = br.readLine().split(" ");
            int k = Integer.parseInt(line[0]);
            int m = Integer.parseInt(line[1]);
            char[] val = line[2].toCharArray();
            TreeSet<String> terms = new TreeSet<>();
            String type = "";
            for (int i = 1; i <= m; i++) {
                String valString = String.valueOf(val);
                if (valString.length() >= 8) {
                    if (valString.substring(0, 4).equals("1233") && valString.substring(valString.length()-4, valString.length()).equals("4444")) {
                        char[] middle = valString.substring(4, valString.length()-4).toCharArray();
                        boolean works = true;
                        for (char c : middle) if (c != '3') { works = false; break; }
                        if (works) { type = "C "+i; break; }
                    } else if (valString.substring(0, 4).equals("5566") && valString.substring(valString.length()-4, valString.length()).equals("7777")) {
                        char[] middle = valString.substring(4, valString.length()-4).toCharArray();
                        boolean works = true;
                        for (char c : middle) if (c != '6') { works = false; break; }
                        if (works) { type = "C "+i; break; }
                    }
                }
                if (terms.contains(valString)) {
                    type = "R "+i;
                    break;
                }

                terms.add(valString);
                if (i != m) val = rats(val);
                // pw.println(val);
            }
            if (type.equals("")) {
                type = String.valueOf(val);
            }
            pw.println(p+" "+type);
        }

        br.close(); pw.close();
    }

    static char[] rats(char[] num) {
        int[] original = new int[num.length], reverse = new int[num.length];
        for (int i = 0; i <= num.length-1; i++) {
            original[i] = num[i]-'0';
            reverse[num.length-1-i] = num[i]-'0';
        }
        int[] sum = new int[num.length];
        for (int i = 0; i <= num.length-1; i++) {
            sum[i] = original[i] + reverse[i];
        }
        int carry = 0;
        for (int i = num.length-1; i >= 0; i--) {
            sum[i] += carry;
            carry = sum[i] / 10;
            sum[i] %= 10;
        }
        String sumString = ""+carry;
        for (int i = 0; i <= num.length-1; i++) sumString += sum[i];
        char[] sumArray = sumString.toCharArray();
        Arrays.sort(sumArray);
        int newLen = sumArray.length;
        int i;
        for (i = 0; i <= newLen-1; i++) if (sumArray[i] != '0') break;
        return Arrays.copyOfRange(sumArray, i, newLen);
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

    static long taxiDist(long x1, long y1, long x2, long y2) {
        // Manhattan distance between two points in the Cartesian coordinate plane
        return Math.abs(x2 - x1) + Math.abs(y2 - y1);
    }
}
