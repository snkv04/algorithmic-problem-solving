import java.util.*;
import java.io.*;

public class Greetings {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;

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
        // int n = Integer.parseInt(br.readLine());
        // TreeSet<Pair> endpoints = new TreeSet<>(Comparator.comparingInt(o -> o.a));
        // while (n-->0) {
        //     int[] person = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        //     endpoints.add(new Pair(person[0], 1));
        //     endpoints.add(new Pair(person[1], -1));
        // }

        // long ans = 0;
        // int count = 0;
        // for (Pair p : endpoints) {
        //     count += p.b;
        //     if (p.b == -1) {
        //         ans += count;
        //     }
        // }
        // pw.println(ans);

        int n = Integer.parseInt(br.readLine());
        Map<Pair, Integer> segments = new TreeMap<>(Comparator.comparingInt(o -> o.b)),
            byA = new TreeMap<>(Comparator.comparingInt(o -> o.a));
        for (int i = 0; i <= n-1; i++) {
            String[] asdf = br.readLine().split(" ");
            segments.put(new Pair(Integer.parseInt(asdf[0]), Integer.parseInt(asdf[1])), i);
            byA.put(new Pair(Integer.parseInt(asdf[0]), Integer.parseInt(asdf[1])), i);
        }
        int[] origIndexToSortedIndex = new int[n];
        int index = 0;
        for (Map.Entry<Pair, Integer> entry : byA.entrySet()) {
            origIndexToSortedIndex[entry.getValue()] = index;
            index++;
        }

        long ans = 0;
        SegmentTree st = new SegmentTree(new int[n]);
        for (Map.Entry<Pair, Integer> entry : segments.entrySet()) {
            int indexByA = origIndexToSortedIndex[entry.getValue()];
            ans += st.query(indexByA, n-1);
            st.update(indexByA, 1);
        }
        pw.println(ans);
    }

    // // // //

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
                t[vertex] = t[2*vertex] + t[2*vertex+1]; // computes the higher-level node afterward
            }
        }

        public long query(int l, int r, int vertex, int vl, int vr) {
            if (l > r)
                return 0;
            if (vl == l && vr == r)
                return t[vertex];
            
            int vm = (vl + vr) / 2; // "vertex's left", "vertex's right", and "vertex's middle"
            return query(l, Math.min(r, vm), 2*vertex, vl, vm) + query(Math.max(l, vm+1), r, 2*vertex+1, vm+1, vr);
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
                t[vertex] = t[2*vertex] + t[2*vertex+1];
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
