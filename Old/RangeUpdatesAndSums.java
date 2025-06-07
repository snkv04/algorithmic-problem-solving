import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class RangeUpdatesAndSums {
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

    static void solve() throws IOException {
        String[] split = br.readLine().split(" ");
        int n = Integer.parseInt(split[0]), q = Integer.parseInt(split[1]);
        int[] arr = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        Lazy st = new Lazy(arr);
        while (q-->0) {
            split = br.readLine().split(" ");
            if (split[0].charAt(0) == '1') {
                int a = Integer.parseInt(split[1]) - 1, b = Integer.parseInt(split[2]) - 1;
                long x = Long.parseLong(split[3]);
                st.update(a, b, 2, x);
            } else if (split[0].charAt(0) == '2') {
                int a = Integer.parseInt(split[1]) - 1, b = Integer.parseInt(split[2]) - 1;
                long x = Long.parseLong(split[3]);
                st.update(a, b, 1, x);
            } else {
                int l = Integer.parseInt(split[1]) - 1, r = Integer.parseInt(split[2]) - 1;
                pw.println(st.sum(l, r));
            }
        }
    }

    // // // //

    static class Multiset { // ordered multiset
        TreeMap<Integer, Integer> map = new TreeMap<>();

        public void add(int x) {
            if (map.containsKey(x)) {
                map.put(x, map.get(x) + 1);
            } else {
                map.put(x, 1);
            }
        }
        
        public void remove(int x) {
            map.put(x, map.get(x) - 1);
            if (map.get(x) == 0) map.remove(x);
        }

        public void add(int x, int q) {
            // q for quantity
            if (map.containsKey(x)) {
                map.put(x, map.get(x) + q);
            } else {
                map.put(x, q);
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

        public SegmentTree(int[] original) {
            n = original.length;
            t = new long[4*n];

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

    static class Lazy {
        int n;
        long[] t;
        long[][] lz;

        public Lazy(int[] original) {
            n = original.length;
            t = new long[4*n];
            lz = new long[4*n][2]; // lz[i][0] == 0: no update, lz[i][0] == 1: set, lz[i][0] == 2: add

            build(original, 1, 0, n-1);
        }

        public void build(int[] a, int vertex, int vl, int vr) {
            if (vl == vr) {
                t[vertex] = a[vl];
            } else {
                int vm = (vl + vr) / 2;
                build(a, 2*vertex, vl, vm);
                build(a, 2*vertex+1, vm+1, vr);
                t[vertex] = t[2*vertex] + t[2*vertex+1];
            }
        }

        public void apply(int v, int vlen, long type, long val) {
            if (type == 2) { // add update
                if (lz[v][0] != 1) {
                    // no set update already there, so this just places an add update with the
                    // previous query's value plus the current query's value
                    lz[v][0] = 2;
                    lz[v][1] = lz[v][1] + val;
                } else {
                    // adds the current query's value to the previous set query's value
                    lz[v][0] = 1;
                    lz[v][1] = lz[v][1] + val;
                }
                t[v] += (long) vlen * val;
            } else if (type == 1) { // set update
                // type == 1
                // the set operation overrides any past updates
                lz[v][0] = 1;
                lz[v][1] = val;
                t[v] = (long) vlen * val;
            }
        }

        public void pushDown(int v, int vl, int vr) {
            int vm = (vl + vr) / 2;
            apply(2*v, vm-vl+1, lz[v][0], lz[v][1]);
            apply(2*v+1, vr-vm, lz[v][0], lz[v][1]);
            lz[v][0] = 0;
            lz[v][1] = 0;
        }

        // range update, but point updates just have l == r
        public void update(int l, int r, long type, long val, int v, int vl, int vr) {
            if (vr < l || vl > r) return;
            if (l <= vl && vr <= r) {
                apply(v, vr-vl+1, type, val);
                return;
            }

            pushDown(v, vl, vr);
            int vm = (vl + vr) / 2;
            update(l, r, type, val, 2*v, vl, vm);
            update(l, r, type, val, 2*v+1, vm+1, vr);
            t[v] = t[2*v] + t[2*v+1];
        }

        public void update(int l, int r, long type, long val) {
            update(l, r, type, val, 1, 0, n-1);
        }

        public long sum(int l, int r, int v, int vl, int vr) {
            if (vr < l || vl > r) return 0;
            if (l <= vl && vr <= r) return t[v];
            
            pushDown(v, vl, vr);
            int vm = (vl + vr) / 2;
            return sum(l, r, 2*v, vl, vm) + sum(l, r, 2*v+1, vm+1, vr);
        }

        public long sum(int l, int r) {
            return sum(l, r, 1, 0, n-1);
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
