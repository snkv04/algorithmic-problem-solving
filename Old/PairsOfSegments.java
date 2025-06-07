import java.util.*;
import java.io.*;

public class PairsOfSegments {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            // int n = Integer.parseInt(br.readLine());
            // ArrayList<Segment> segs = new ArrayList<>();
            // for (int i = 0; i <= n-1; i++) {
            //     String[] line = br.readLine().split(" ");
            //     segs.add(new Segment(Integer.parseInt(line[0]), Integer.parseInt(line[1])));
            // }
            // Collections.sort(segs);

            // int count = 0;
            // int latest = -1;
            // while (!segs.isEmpty()) {
            //     Segment left = segs.remove(0);
            //     if (left.l <= latest) continue;
            //     // pw.println("checking against "+left+", current="+segs);
            //     for (int i = 0; i <= segs.size()-1; i++) {
            //         // pw.println("\tchecking "+segs.get(i));
            //         if (left.intersects(segs.get(i)) && segs.get(i).l > latest) {
            //             count += 2;
            //             // pw.println("\t"+segs.get(i)+" works");
            //             latest = segs.remove(i).r;
            //             break;
            //         }
            //     }
            // }
            // pw.println(n-count);

            // the above algorithm sorts by earliest ending segment, and then tries to
            // find the earliest ending segment that intersects it. this fails in some special
            // cases (such as the one below). essentially, it doesn't consider that the other
            // segment in the pair can make the solution inoptimal.
            //               ___    __
            //             ____    ____
            // __________
            //     ______________________
            // to rectify this, instead of sorting by earliest ending independent segment,
            // we should first consider all possible intersections of segments (this is like
            // taking all pairs but excluding those that don't intersect), sort those
            // new intersection-segments by earliest ending, and then selecting as many as
            // possible that don't intersect with each other. this way, we take into consideration
            // the full intersection of each pair from start to finish (basically, take into
            // consideration both segments in an intersection-segment), and it is therefore
            // a thorough, complete, and correct solution. it's kind of like brute-forcing all
            // pairs.
            int n = Integer.parseInt(br.readLine());
            ArrayList<Segment> segments = new ArrayList<Segment>();
            for (int i = 1; i <= n; i++) {
                String[] line = br.readLine().split(" ");
                segments.add(new Segment(Integer.parseInt(line[0]), Integer.parseInt(line[1])));
            }
            ArrayList<Segment> intersectingPairs = new ArrayList<>();
            for (int i = 0; i <= n-1; i++) {
                for (int j = i+1; j <= n-1; j++) {
                    Segment one = segments.get(i);
                    Segment two = segments.get(j);
                    if (one.intersects(two))
                        intersectingPairs.add(new Segment(
                            Math.min(one.l, two.l), Math.max(one.r, two.r)
                        ));
                }
            }
            intersectingPairs.sort(Comparator.comparingInt(o -> o.r));
            
            int count = 0, latest = -1;
            for (int i = 0; i <= intersectingPairs.size()-1; i++) {
                if (intersectingPairs.get(i).l > latest) {
                    count += 2;
                    latest = intersectingPairs.get(i).r;
                }
            }
            pw.println(n-count);
        }

        br.close(); pw.close();
    }

    static class Segment {
        int l, r;

        public Segment(int l, int r) {
            this.l = l;
            this.r = r;
        }

        // public boolean intersects(Segment other) {
        //     return other.l <= this.r;
        // }

        // public int compareTo(Segment other) {
        //     if (this.r != other.r) return Integer.compare(this.r, other.r);
        //     else return Integer.compare(this.l, other.l);
        // }

        public String toString() {
            return "(l="+l+", r="+r+")";
        }

        public boolean intersects(Segment other) {
            return other.l <= this.r && this.l <= other.r;
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
}
