import java.util.*;
import java.io.*;

public class PowerOfPoints {
    public static void main(String[] args) throws IOException {
        /*
         * First off, since the points we have the compute the "powers" of range from
         * 1 to 1e9, we can't directly scan over them. We can remodel the way we calculate
         * the sums of the powers of the points by making one important observation: if a
         * segment ranges from a to b (where a < b), then the number of points whose power
         * increases by 1 (which is b-a+1) is equivalent to the length of the segment (b-a+1).
         * So, the total increase in the sum of the points' powers across the entire number
         * line is just the length of the segment. Additionally, if multiple segments overlap
         * over a set of points, those points will just have a power of 2 instead of 1, so
         * the sums of powers will still just be the sums of the segments' lengths. Now, we
         * just need to calculate the sums of all the segments' lengths under all the given
         * conditions efficiently.
         * Temporarily suppose that the points are all sorted. If s = the first point, then
         * we can find the sum of the segments' lengths by summing up x1-x1, x2-x1, x3-x1, etc.
         * Now, if we did the same for all of the remaining points, the time complexity of
         * the algorithm would be O(n^2), which would be too slow since 1<=n<=2e5. If we
         * imagine the segments as lines connecting every single point (including the first
         * point) to the first point, then we just have to move the center of points from
         * one to the next over and over until the point that connects to all the points is
         * the last one. What is the difference in segment lengths between one point being
         * the one that connects to every other and the next point fulfilling that role?
         * If in one "step" we move from p_new to p_old, where p_new >= p_old, then the 
         * distance of p_new - p_old would be subtracted for all the segments going to the
         * right of p_new and would be added for all of the segments going to the left of
         * p_old, while the segment between p_new and p_old would actually remain unchanged
         * for the current step. In this way, we can relate each sum to the last, and find
         * all the answers we need.
         * Now, to deal with the fact that the points aren't all initially sorted from left
         * to right, we can associate the index each point was initially given at, the point
         * itself, and the answer for if s = that point together. Before calculating the sums,
         * we can sort these triplets by the point value, and then after calculating them,
         * we can sort the triplets by the original index to output the answers in the correct
         * order.
         */

        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] x = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            long[][] arr = new long[n][3];
            for (int i = 0; i <= n-1; i++) {
                arr[i] = new long[] {i, x[i], 0};
            }
            Arrays.sort(arr, Comparator.comparingLong(o -> o[1]));

            long sum = 0;
            for (int xi : x) {
                sum += xi + 1 - arr[0][1];
            }
            arr[0][2] = sum;

            for (int i = 1; i <= n-1; i++) {
                sum -= ((long) n-1-i) * (arr[i][1] - arr[i-1][1]);
                sum += ((long) i-1) * (arr[i][1] - arr[i-1][1]);
                arr[i][2] = sum;
            }

            Arrays.sort(arr, Comparator.comparingLong(o -> o[0]));
            for (int i = 0; i <= n-1; i++) {
                pw.print(arr[i][2]+" ");
            }
            pw.println();
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

    static class Pair {
        int a, b;

        public Pair(int a, int b) {
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
    }
}
