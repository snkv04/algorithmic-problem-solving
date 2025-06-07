import java.util.*;
import java.io.*;

public class SumAndProduct {
    static Multiset nums;

    public static void main(String[] args) throws IOException {
        /*
         * One way to solve problem is to first find out how ai and aj can be written in
         * terms of x and y. Given that ai + aj = x and ai * aj = y, we can rewrite the
         * equation as follows:
         * ai + aj = x
         * --> ai + y/ai = x
         * --> (ai^2 + y) / ai = x
         * --> ai^2 + y = x * ai
         * --> ai^2 - x*ai + y = 0
         * which we can then solve with the quadratic formula to give
         * ai = (x ± sqrt(x^2 - 4y)) / 2.
         * This shows that there are two roots, which would then be the values of
         * ai and aj. Also, since the set of solutions to this system is no larger than
         * 2, we know that we only have to check for pairs of elements with these two 
         * values and none others. Now, for actually checking the pairs, we can just
         * find the number of elements with value ai and number of elements with value
         * aj and then multiply these two numbers. If ai = aj (in other words, if the
         * discriminant from the solution to the quadratic equation is equal to 0),
         * then we can just count the number of pairs that satisfy the conditions with
         * the formula C(count(ai), 2). The counts of each element can be kept track
         * of using a multiset.
         */

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            Multiset multiset = new Multiset();
            for (int i = 0; i <= n-1; i++) {
                multiset.add(a[i]);
            }

            int q = Integer.parseInt(br.readLine());
            while (q-->0) {
                String[] split = br.readLine().split(" ");
                long x = Long.parseLong(split[0]), y = Long.parseLong(split[1]);
                pw.print(countPairs(multiset, x, y) + " ");
            }
            pw.println();
        }

        br.close(); pw.close();
    }

    static long countPairs(Multiset multiset, long x, long y) {
        long discriminant = x*x - 4*y;
        if (discriminant < 0) {
            return 0;
        }
        long sqrt = sqrt(discriminant);
        // System.out.println("x = "+x+", y = "+y+", d = "+discriminant);
        if (sqrt * sqrt != discriminant) {
            return 0;
        }

        long ai = x + sqrt;
        // System.out.println("ai * 2 = "+ai);
        if (ai % 2 == 1) {
            return 0;
        }

        ai /= 2;
        long aj = (x - sqrt) / 2;
        if (ai == aj) {
            long count = multiset.count(ai);
            return (count * (count - 1)) / 2;
        } else {
            long count1 = multiset.count(ai), count2 = multiset.count(aj);
            return count1 * count2;
        }
    }

    // // // //

    static class Multiset {
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

        public int count(long x) {
            if (!mset.containsKey(x)) return 0;
            return mset.get(x);
        }

        // public void add(int x, int q) {
        //     // q for quantity
        //     if (mset.containsKey(x)) {
        //         mset.put(x, mset.get(x) + q);
        //     } else {
        //         mset.put(x, q);
        //     }
        // }
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
