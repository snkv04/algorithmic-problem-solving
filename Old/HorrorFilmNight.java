import java.util.*;
import java.io.*;

public class HorrorFilmNight {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int[] emma = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int[] marcos = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        TreeSet<Integer> emma2 = new TreeSet<>(); for (int i = 1; i <= emma.length-1; i++) { emma2. add(emma[i]);}
        TreeSet<Integer> marcos2 = new TreeSet<>(); for (int i = 1; i <= marcos.length-1; i++) marcos2.add(marcos[i]);
        
        TreeSet<Integer> distinct = new TreeSet(); for (int num : emma2) distinct.add(num); for (int num : marcos2) distinct.add(num);
        if (distinct.size()==0) {
            pw.print(0);
            pw.close();
            return;
        }
        boolean[][] like = new boolean[distinct.size()][2];
        int numMovies = distinct.size();
        for (int i = 0; i <= numMovies-1; i++) {
            int movie = distinct.pollFirst();
            if (emma2.contains(movie)) like[i][0] = true;
            if (marcos2.contains(movie)) like[i][1] = true;;
        }
        // for (int i = 0; i <= numMovies-1; i++) pw.println(Arrays.toString(like[i]));

        // int[][] memo =  new int[numMovies+1][2];
        // for (int i = 1; i <= numMovies; i++) {
        //     memo[i][0] = Math.max(memo[i-1][0], memo[i-1][1]);
        //     memo[i][1] = memo[i-1][0];
        //     if () memo[i][1] = Math.max(memo[i][1], memo[i-1][0]);
        // }
        int start = -1;
        for (int i = 0; i <= numMovies-1; i++) {
            if (like[i][0] || like[i][1]) {
                start = i;
                break;
            }
        }
        if (start==-1) { pw.print(0); pw.close(); return; }
        int ans = 1;
        boolean last1 = like[start][0], last2 = like[start][1];
        // pw.println("watching "+start);
        for (int i = start+1; i <= numMovies - 1; i++) {
            if ((like[i][0]==false&&like[i][1]==false)
                || (like[i][0]==last1&&last1==false) || (like[i][1]==last2&&last2==false)) {

                continue;
            }
            ans++;
            // pw.println("doing "+i);
            last1 = like[i][0];
            last2 = like[i][1];
        }
        pw.println(ans);

        br.close(); pw.close();
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
}
