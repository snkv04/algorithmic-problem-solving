import java.util.*;
import java.io.*;

public class SellingAMenagerie {
    static Stack<Integer> reverse;
    static int n;
    static int[] a, c;
    static boolean[] visited;
    static ArrayList<Integer> order;
    static int[] position;
    static int count;
    static int min, minNode;
    static int[] startAt;
    static int[] newPos;
    static TreeSet<Integer> unused;
    static PrintWriter pw;
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            n = Integer.parseInt(br.readLine());
            a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            c = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            for (int i = 0; i <= n-1; i++) a[i]--; // is basically an adjacency list array
            visited = new boolean[n];
            reverse = new Stack<>();

            for (int i = 0; i <= n-1; i++) {
                if (!visited[i]) {
                    dfs(i);
                }
            }

            // pw.println(Arrays.toString(a));
            // pw.println(reverse);
            int index = 0;
            order = new ArrayList<>();
            position = new int[n];
            while (!reverse.isEmpty()) {
                position[reverse.peek()] = index;
                order.add(reverse.peek());
                reverse.pop();
                index++;
            }

            visited = new boolean[n];
            // min = Integer.MAX_VALUE; minNode = -1;
            startAt = new int[n];
            newPos = new int[n];
            for (int i = 0; i <= n-1; i++) {
                if (position[i] > position[a[i]]) {
                    count = 0;
                    min = Integer.MAX_VALUE; minNode = -1;
                    dfs2(i);
                    dfs3(i, a[minNode]);
                }
            }

            // pw.println(order);
            // pw.println(Arrays.toString(startAt));
            // pw.println(Arrays.toString(newPos));
            unused = new TreeSet<>(); for (int i = 0; i <= n-1; i++) unused.add(i);
            visited = new boolean[n];
            for (int num : order) {
                if (newPos[num] != -1) {
                    unused.remove(num);
                    pw.print((num+1) + " ");
                } else {
                    if (unused.contains(num)) {
                        dfs4(startAt[num]);
                    }
                }
                // pw.print((num+1)+" "); // this random ass fucking line stopped me from getting F :(
            }
            pw.println();
        }

        br.close(); pw.close();
    }

    static void dfs(int node) {
        visited[node] = true;
        if (!visited[a[node]]) dfs(a[node]);
        reverse.add(node);
    }

    static void dfs2(int node) {
        visited[node] = true;
        newPos[node] = -1;
        count++;
        if (c[node] < min) {
            min = c[node];
            minNode = node;
        }
        if (!visited[a[node]]) dfs2(a[node]);
    }

    static void dfs3(int node, int start) {
        if (count==0) return;
        count--;
        startAt[node] = start;
        dfs3(a[node], start);
    }

    static void dfs4(int node) {
        
        visited[node] = true;
        unused.remove(node);
        pw.print((node+1)+" ");
        if (!visited[a[node]]) dfs4(a[node]);
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
