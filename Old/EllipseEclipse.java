import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class EllipseEclipse {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static int[] di = {0, 0, 1, -1}, dj = {1, -1, 0, 0};

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    // static void solve() throws IOException {
    //     /*
    //      * first, fidn the point at which the major axis is. we can do this by splitting it in half.
    //      * finding th emidpoint of the two foci, and going off from the middle to one of the foci in the
    //      * length of the major axis/2. now we know where it is. we can find the "constant value", by just
    //      * adding up the distance from this point to both foci.
    //      * 
    //      * now we have the constant value, c.
    //      * 
    //      * frist, look at the upper focus, with coordinates (x1, y1). consider the point with
    //      * coords (x1, smth), where smth is the maximum y value that we can get where that point
    //      * is equidistant from both foci.
    //      * 
    //      * do the same with the rightmost focus.
    //      */
    //     int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
    //     double x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3], major = a[4];
    //     double semi = major / 2.0;
    //     double midx = (x1 + x2) / 2.0, midy = (y1 + y2) / 2.0;
    //     double slope = (double) (y2 - y1) / (double) (x2 - x1);
    //     double endx, endy;
    //     if (x1 == x2) {
    //         endx = midx;
    //         endy = midy + semi;

    //         // take care of return value
    //     } else if (y1 == y2) {
    //         endy = midy;
    //         endx = midx + semi;
    //         // take care of return value
    //     } else {
    //         endx = midx + semi * Math.cos(Math.atan(slope));
    //         endy = midx + semi * Math.sin(Math.atan(slope));
    //     }
    //     double c = dist(x1, y1, endx, endy) + dist(x2, y2, endx, endy);
    //     pw.println(c);
        

    //     Point[] points = {new Point(x1, y1), new Point(x2, y2)};
    //     Arrays.sort(points, Comparator.comparingDouble(o -> o.x));
    //     double l = Integer.MIN_VALUE/2, r = Integer.MAX_VALUE/2, xmin = -1;
    //     for (int i = 1; i <= 80; i++) {
    //         double mid = (l + r) / 2;
    //         double px = mid, py = points[0].y;
    //         if (dist(px, py, ))
    //     }
    //     int n = Integer.parseInt(br.readLine());
    // }

    // static void solve() throws IOException {
    //     // let centerX = 350;
    //     // let centerY = 100;
    //     // let radiusX = 100;
    //     // let radiusY = 50;
    //     // let degrees = 200;

    //     // let radians = degrees * (Math.PI / 180);
    //     // let radians90 = radians + Math.PI / 2;
    //     // let ux = radiusX * Math.cos(radians);
    //     // let uy = radiusX * Math.sin(radians);
    //     // let vx = radiusY * Math.cos(radians90);
    //     // let vy = radiusY * Math.sin(radians90);

    //     // let width = Math.sqrt(ux * ux + vx * vx) * 2;
    //     // let height = Math.sqrt(uy * uy + vy * vy) * 2;
    //     // let x = centerX - (width / 2);
    //     // let y = centerY - (height / 2);
        
    //     int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
    //     double x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3], major = a[4];
    //     double semi = major / 2.0;
    //     double midx = (x1 + x2) / 2.0, midy = (y1 + y2) / 2.0;
    //     double slope = (double) (y2 - y1) / (double) (x2 - x1);
    //     double endx, endy;


    //     /*
    //      * find the lowest y such that the point there is equidistant
    //      */
    //     double d = Math.max(y1, y2), u = 1e9, uppery = -1;
    //     for (int i = 1; i <= 80; i++) {

    //     }
    // }

    static void solve() throws IOException {
        /*
         * first, find the upper point. then, use ternary search on the angle to find the angle at which
         * the point on the ellipse is highest in terms of y value. to find the point on the ellilpse, use
         * binary search on the distance from the point to find the furthest point such that the sum of the 
         * distances between the point and both foci is less than or equal to the constant value.
         * the maximum y value minus the upper focus can just be subtracted from the lower focus's y-value
         * to get the min. same logic for rightmost x-value and leftmost x-value
         */
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        double x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3], major = a[4];
        if (x1 == x2) {
            //
        }
        if (y1 == y2) {
            //
        }
        
        Point[] points = {new Point(x1, y1), new Point(x2, y2)};
        double c = major;
        Arrays.sort(points, Comparator.comparingDouble(o -> o.x));
        double l = -1 * Math.PI / 2 + 1e-9, r = Math.PI / 2 - 1e-9, maxX = -1;
        for (int i = 1; i <= 100; i++) {
            double mid1 = l + (r - l) / 3.0;
            double mid2 = r - (r - l) / 3.0;
            Point p1 = find(points, c, mid1), p2 = find(points, c, mid2);
            if (p1.x <= p2.x) {
                l = mid1;
                maxX = p2.x;
            } else {
                r = mid2;
                maxX = p1.x;
            }
        }
        double minX = points[0].x - (maxX - points[1].x);

        l = 1e-9; r = Math.PI - 1e-9; double maxY = -1;
        Arrays.sort(points, Comparator.comparingDouble(o -> o.y));
        for (int i = 1; i <= 100; i++) {
            double mid1 = l + (r - l) / 3.0;
            double mid2 = r - (r - l) / 3.0;
            Point p1 = find(points, c, mid1), p2 = find(points, c, mid2);
            if (p1.y <= p2.y) {
                l = mid1;
                maxY = p2.y;
            } else {
                r = mid2;
                maxY = p1.y;
            }
        }
        double minY = points[0].y - (maxY - points[1].y);

        pw.println(minX+" "+minY+" "+maxX+" "+maxY);
    }

    static double dist(double x1, double y1, double x2, double y2) {
        double dx = x2 - x1, dy = y2 - y1;
        return Math.sqrt(dx * dx + dy * dy);
    }

    static Point find(Point[] points, double distSum, double angle) {
        double l = 1e-9, r = 1e9, ans = -1;
        for (int i = 1; i <= 100; i++) {
            double mid = (l + r) / 2;
            double newx, newy;
            if (Math.abs(angle - Math.PI / 2) <= 1e-9) {
                newx = points[1].x;
                newy = points[1].y + mid;
            } else {
                newx = points[1].x + mid * Math.cos(angle);
                newy = points[1].y + mid * Math.sin(angle);
            }
            if (dist(newx, newy, points[1].x, points[1].y) + dist(newx, newy, points[0].x, points[0].y) <= distSum) {
                ans = l = mid;
            } else {
                r = mid;
            }
        }
        
        if (Math.abs(angle - Math.PI / 2) <= 1e-9) {
            return new Point(points[1].x, points[1].y + ans);
        } else {
            return new Point(points[1].x + ans * Math.cos(angle), points[1].y + ans * Math.sin(angle));
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
        long[][] lz;

        public SegmentTree(int[] original) {
            n = original.length;
            t = new long[4*n];
            lz = new long[4*n][2]; // lz[i][0] == no update, lz[i][1] == set, lz[i][2] == add

            build(original, 1, 0, n-1);
        }

        public void build(int[] a, int vertex, int vl, int vr) {
            if (vl == vr) {
                t[vertex] = a[vl];
            } else {
                int vm = (vl + vr) / 2;
                build(a, 2*vertex, vl, vm);
                build(a, 2*vertex+1, vm+1, vr);
                t[vertex] = Math.max(t[2*vertex], t[2*vertex+1]);
            }
        }

        // l and r are the bounds of the query; vl and vr are the bounds of the current vertex
        public long query(int l, int r, int vertex, int vl, int vr) {
            if (l > r)
                return Long.MIN_VALUE / 2;
            if (vl == l && vr == r)
                return t[vertex];
            
            int vm = (vl + vr) / 2;
            return Math.max(
                query(l, Math.min(r, vm), 2*vertex, vl, vm),
                query(Math.max(l, vm+1), r, 2*vertex+1, vm+1, vr)
            );
        }

        public long query(int l, int r) {
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
        // int i, j;

        // public Point(int i, int j) {
        //     this.i = i;
        //     this.j = j;
        // }

        double x, y;

        public Point(double x, double y) {
            this.x = x;
            this.y = y;
        }
    }

    // static class DSU2 {
    //     // 2-dimensional DSU
    //     // this may or may not be useless since a 2D array can just be mapped to a 1D array :/
    //     Point[][] parent;
    //     int[][] size;

    //     public DSU2(int r, int c) {
    //         parent = new Point[r][c];
    //         size = new int[r][c];
    //         for (int i = 0; i <= r-1; i++) {
    //             for (int j = 0; j <= c-1; j++) {
    //                 parent[i][j] = new Point(i, j);
    //             }
    //         }
    //         for (int i = 0; i <= r-1; i++) {
    //             Arrays.fill(size[i], 1);
    //         }
    //     }

    //     public Point find(int i, int j) {
    //         if (parent[i][j].i == i && parent[i][j].j==j) {
    //             return parent[i][j];
    //         } else {
    //             parent[i][j] = find(parent[i][j].i, parent[i][j].j);
    //             return parent[i][j];
    //         }
    //     }

    //     public void union(int ai, int aj, int bi, int bj) {
    //         Point c = find(ai, aj);
    //         Point d = find(bi, bj);
    //         if (c.i != d.i || c.j != d.j) {
    //             int sum = size[c.i][c.j] + size[d.i][d.j];
    //             parent[d.i][d.j] = c;
    //             size[c.i][c.j] = sum;
    //             size[d.i][d.j] = sum;
    //         }
    //     }

    //     public int size(int i, int j) {
    //         return size[i][j];
    //     }
    // }

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

    // this runs the Extended Euclidean Algorithm on inputs a and b,
    // and it returns a length-3 array in the form [g, x, y],
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

    static class PrefixTree {
        class TrieNode {
            TrieNode[] children;
            int end;
    
            public TrieNode() {
                children = new TrieNode[26];
                end = 0;
            }
        }
    
        private TrieNode root;
    
        public PrefixTree() {
            root = new TrieNode();
        }
        
        public void insert(String str) {
            TrieNode curr = root;
            for (int i = 0; i <= str.length() - 1; i++) {
                int letter = str.charAt(i) - 'a';
                if (curr.children[letter] == null) {
                    curr.children[letter] = new TrieNode();
                }
                curr = curr.children[letter];
            }
            curr.end++;
        }
        
        public boolean search(String str) {
            TrieNode curr = root;
            for (int i = 0; i <= str.length() - 1; i++) {
                int letter = str.charAt(i) - 'a';
                if (curr.children[letter] == null) {
                    return false;
                }
                curr = curr.children[letter];
            }
            return curr.end > 0;
        }
        
        public boolean startsWith(String prefix) {
            TrieNode curr = root;
            for (int i = 0; i <= prefix.length() - 1; i++) {
                int letter = prefix.charAt(i) - 'a';
                if (curr.children[letter] == null) {
                    return false;
                }
                curr = curr.children[letter];
            }
            return true;
        }

        public void delete(String str) {
            _delete(str, this.root, -1);
        }

        public boolean _delete(String str, TrieNode node, int index) {
            // reached the last letter
            if (index + 1 == str.length()) {
                // if the last letter isn't marked with end > 0, then the
                // word doesn't exist in the trie
                if (node.end == 0) {
                    return false;
                }

                // unmarks the node as the end of a word
                node.end--;

                // if there are other copies of the same word in the trie,
                // then return false (meaning we shouldn't delete any nodes
                // higher on the path from the root)
                if (node.end > 0) {
                    return false;
                }

                // since this word is now no longer part of the trie, we check
                // if any other words use this word as a prefix; if so, then we
                // delete nothing higher on the path from the path, but if not,
                // then we indicate that we can set this node as null from the
                // perspective of the parent node
                for (int i = 0; i <= 25; i++) {
                    if (node.children[i] != null) {
                        return false;
                    }
                }
                return true;
            }

            // not on last letter
            int nextLetter = str.charAt(index + 1) - 'a';

            // if the next letter is not in the trie, then the word isn't in the trie
            if (node.children[nextLetter] == null) {
                return false;
            } else {
                // if we don't want to delete the next letter from the trie, we don't
                // want to delete anything higher on the path from the root to the
                // current node, and so this cascades up
                if (_delete(str, node.children[nextLetter], index + 1) == false) {
                    return false;
                }
                
                // delete the next letter from the trie
                node.children[nextLetter] = null;

                // now, we just check if the current node is needed for any other words
                // (i.e., if it's a prefix of any); if it is, then we don't want to delete
                // anything further, and if it isn't, then we tell the node above to delete
                // this current node
                for (int i = 0; i <= 25; i++) {
                    if (node.children[i] != null) {
                        return false;
                    }
                }
                return true;
            }
        }

        public void printTrie() {
            _printTrie(0, '.', this.root);
        }

        public void _printTrie(int tab, char c, TrieNode node) {
            for (int i = 1; i <= tab; i++) System.out.print(' ');
            System.out.println("(\"" + c + "\", " + node.end + ")");
            for (int i = 0; i <= 25; i++) {
                if (node.children[i] != null) {
                    _printTrie(tab + 2, (char) ('a' + i), node.children[i]);
                }
            }
        }
    }
}
