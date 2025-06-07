import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class YunlisSubarrayQueries {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static int[] di = {0, 0, 1, -1}, dj = {1, -1, 0, 0};

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine()); // 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        /*
         * we can start off by precomputing the answers for each size-k window.
         *      by the way, how can this be done? having a sequence of n elements a_1, a_2, ..., a_n
         *      be consecutively increasing is the same as having the sequence
         *      a_1 - 1, a_2 - 2, ..., a_i - i, ..., a_n - n consist of all the same elements. so, we
         *      can replace all of the elements with these, and then use a sliding window technique
         *      to compute the minimum changes needed: for a given window, the number of changes needed
         *      is the length of the window minus the largest frequency. this can be computed by having
         *      a multiset of the elements for the current window we are looking at and having a sorted
         *      multiset of the frequencies of the elements so that we can conveniently get the largest
         *      frequency. we need a multiset so we actually store all the information that we need and
         *      don't accidentally store only one instance of a frequency if there are multiple elements
         *      in the window with that frequency.
         * so, ans[r] will effectively equal f(a[r-k+1, r-k+2, ..., r]). now, for computing
         * the requested summation, we first off want to calculate the sum as i goes from l+k-1 to r of
         * f(a[l, l+1, l+2, ..., i]). consider an arbitrary array c. it's clear that, by a simple brute
         * force algorithm, f(c) is equal to the minimum of f(d) across all length-k subarrays called d
         * contained within c. therefore, what we want to calculate for each query is
         * the sum as i goes from l+k-1 to r of min(ans[l+k-1], ans[l+k], ..., ans[i]).
         * given that that is the problem that we wish to solve, let's take a closer look at the ans
         * array. this is generally applicable to any array (i.e., is not specific to the calculations
         * that resulted in the ans array), but if l was equal to 1 (or 0, if we are using 0-indexing),
         * then we are looking for the sum of all the prefix minimums up to the rth element.
         * now, the issue is that l is changing across all the queries. if we try to preprocess the
         * prefix minimum array, then the problem is that for a given range [li, ri] of a query, the
         * values of the prefix minimum array within that range could be influenced by some small values
         * to the left of that range, which should not impact the calculation for that specific query,
         * so we need some way of constructing the prefix minimum array intelligently where once we
         * compute the answer for a given query, it doesn't invalidate the calculations for any future
         * queries.
         * for this exact reason, we can process the queries in order of right-to-left values of l. for
         * each query, we compute the new prefix minimum array by making it so that for a given element
         * m_i at index i, all elements to the right of it that are greater than it until the first that
         * is less than it are set to m_i. this can be done using a lazy segment tree, and the sums can
         * also be taken using the same segment tree. for each element, the index that we need to update
         * until (which is some point to the right or on the element) can easily be found either using a
         * monotonic stack or binary search.
         */

        String[] str = br.readLine().split(" ");
        int n = Integer.parseInt(str[0]), k = Integer.parseInt(str[1]), q = Integer.parseInt(str[2]);
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int[] ans = new int[n];
        Multiset diffs = new Multiset(), freqs = new Multiset();
        for (int i = 0; i <= k-1; i++) {
            diffs.add(a[i]-i);
        }
        for (Map.Entry<Integer, Integer> entry : diffs.mset.entrySet()) {
            freqs.add(entry.getValue());
        }
        ans[k-1] = k - freqs.mset.lastKey();

        for (int r = k; r <= n-1; r++) {
            int adding = a[r]-r, removing = a[r-k]-r+k;
            freqs.remove(diffs.count(removing));
            diffs.remove(removing);
            if (diffs.count(removing) > 0) freqs.add(diffs.count(removing));

            if (diffs.count(adding) > 0) freqs.remove(diffs.count(adding));
            diffs.add(adding);
            freqs.add(diffs.count(adding));

            ans[r] = k - freqs.mset.lastKey();
        }
        // pw.println("ans = "+Arrays.toString(ans));

        Stack<Integer> monotonic = new Stack();
        int[] rangeRight = new int[n];
        for (int i = k-1; i <= n; i++) {
            int currVal = i==n ? -1 : ans[i];
            while (!monotonic.isEmpty() && ans[monotonic.peek()] > currVal) {
                int idx = monotonic.pop();
                rangeRight[idx] = i-1;
            }
            monotonic.add(i);
        }
        // pw.println("rangeright = "+Arrays.toString(rangeRight));

        long[][] queries = new long[q][4];
        for (int i = 0; i <= q-1; i++) {
            str = br.readLine().split(" ");
            int l = Integer.parseInt(str[0])-1, r = Integer.parseInt(str[1])-1;
            queries[i] = new long[] {i, l, r, 0};
        }
        Arrays.sort(queries, Comparator.comparingLong(o -> o[1])); // comparing by left bound of query

        int prevLpKm1 = n;
        Lazy st = new Lazy(new int[n]);
        for (int i = q-1; i >= 0; i--) {
            long l = queries[i][1], r = queries[i][2];
            for (int j = prevLpKm1-1; j >= l+k-1; j--) {
                st.update(j, rangeRight[j], 1, ans[j]);
            }
            prevLpKm1 = (int) l+k-1;
            queries[i][3] = st.sum((int)(l+k-1), (int)r);
        }
        Arrays.sort(queries, Comparator.comparingLong(o -> o[0])); // sorting queries in original order

        for (int i = 0; i < q; i++) {
            pw.println(queries[i][3]);
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

        public int count(int x) {
            if (!mset.containsKey(x)) {
                return 0;
            } else {
                return mset.get(x);
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

    static class Lazy {
        int n;
        long[] t;
        long[][] lz;

        public Lazy(int[] original) {
            n = original.length;
            t = new long[4*n];
            lz = new long[4*n][2]; // lz[i][0] == 0: no update, lz[i][0] == 1: set

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
            if (type == 1) { // set update
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
