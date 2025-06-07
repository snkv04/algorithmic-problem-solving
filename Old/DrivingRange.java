import java.util.*;
import java.io.*;

public class DrivingRange {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static int[] di = {0, 0, 1, -1}, dj = {1, -1, 0, 0};
    static int n, m;
    static int[][] edges;

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
        String[] split = br.readLine().split(" ");
        n = Integer.parseInt(split[0]); m = Integer.parseInt(split[1]);
        edges = new int[m][3];
        for (int i = 0; i <= m-1; i++) {
            edges[i] = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        }

        long ans = -1, l = 0, r = Integer.MAX_VALUE;
        while (l <= r) {
            long mid = (l + r) / 2;
            if (check(mid)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        pw.println(ans==-1?"IMPOSSIBLE":ans);
    }

    static boolean check(long maxLength) {
        DSU dsu = new DSU(n);
        for (int i = 0; i <= m-1; i++) {
            if (edges[i][2] <= maxLength) {
                dsu.union(edges[i][0], edges[i][1]);
            }
        }

        HashSet<Integer> distinctComponents = new HashSet<>();
        for (int i = 0; i <= n-1; i++) {
            distinctComponents.add(dsu.find(i));
        }
        return distinctComponents.size() == 1;
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
