import java.util.*;
import java.io.*;

public class TornToPieces {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        String[][] input = new String[n][0];
        for (int i = 0; i <= n-1; i++) input[i] = br.readLine().split(" ");
        // HashMap<String, Integer> dict = new HashMap();
        // String[] name = new String[n];
        // for (int i = 0; i <= n-1; i++) { dict.put(input[i][0], i); name[i] = input[i][0]; }
        TreeMap<String, ArrayList<String>> adjLists = new TreeMap<String, ArrayList<String>>();
        for (int i = 0; i <= n-1; i++) {
            String from = input[i][0];
            for (int j = 1; j <= input[i].length-1; j++) {
                String to = input[i][j];
                ArrayList<String> adj;
                if (adjLists.containsKey(from)) {
                    adj = adjLists.get(from);
                } else {
                    adj = new ArrayList<>();
                }
                if (!adj.contains(to)) adj.add(to);
                adjLists.put(from, adj);

                adj = new ArrayList<>();
                if (adjLists.containsKey(to)) adj = adjLists.get(to);
                if (!adj.contains(from)) adj.add(from);
                adjLists.put(to, adj);
            }
        }
        // for (int i = 0; i <= n-1; i++) {
        //     int from = dict.get(input[i][0]);
        //     for (int j = 1; j <= input[i].length-1; j++) {
        //         adjLists[from].add(dict.get(input[i][j]));
        //     }
        // }
        // for (int i = 0; i <= n-1; i++) {
        //     pw.println("i="+i+", and adj="+adjLists[i]);
        // }
        // System.out.println(dict);
        // System.out.println(Arrays.toString(name));
        // for (Map.Entry entry : adjLists.entrySet()) {
        //     pw.println("from="+entry.getKey()+", to="+entry.getValue());
        // }

        String[] line = br.readLine().split(" ");
        String start = line[0], end = line[1];

        // obviously a tree so dfs is fine, dijkstra is overkill (especially with the node
        // names being strings)
        TreeMap<String, Boolean> visited = new TreeMap<>();
        for (Map.Entry<String, ArrayList<String>> entry : adjLists.entrySet()) visited.put(entry.getKey(), false);
        TreeMap<String, String> prev = new TreeMap<>();
        for (Map.Entry<String, ArrayList<String>> entry : adjLists.entrySet()) prev.put(entry.getKey(), entry.getKey());

        if (!prev.containsKey(start) || !prev.containsKey(end)) {
            pw.println("no route found");
            pw.close();
            return;
        }
        
        Stack<String> s = new Stack<String>();
        s.add(start);
        while (!s.isEmpty()) {
            String node = s.pop();
            if (visited.get(node).equals(true)) continue;

            visited.put(node, true);
            for (String next : adjLists.get(node)) {
                if (visited.get(next)==false) {
                    prev.put(next, node);
                    s.add(next);
                }
            }
        }

        Stack<String> path = new Stack<>();
        path.add(end);
        String last = prev.get(end);
        while (!path.peek().equals(last)) {
            path.add(last);
            last = prev.get(last);
        }

        if (! path.peek().equals(start)) pw.println("no route found");
        else while (!path.isEmpty()) pw.print(path.pop() + " ");

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
