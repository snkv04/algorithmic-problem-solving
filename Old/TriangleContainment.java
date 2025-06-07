import java.util.*;
import java.io.*;

public class TriangleContainment {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static long dist;

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
        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        dist = Integer.parseInt(line[1]);
        Point[] pts = new Point[n];
        PriorityQueue<Point> pq = new PriorityQueue<>(new Comp2());
        for (int i = 0; i <= n-1; i++) {
            line = br.readLine().split(" ");
            Point p = new Point(Integer.parseInt(line[0]), Integer.parseInt(line[1]), Integer.parseInt(line[2]), i);
            pq.add(p);
            pts[i] = p;
        }
        Arrays.sort(pts, new Comp());
        int[] origIndexToSortedIndex = new int[n];
        for (int i = 0; i <= n-1; i++) origIndexToSortedIndex[pts[i].index] = i;

        long[] ans = new long[n];
        SegmentTree st = new SegmentTree(new int[n]); // follows ordering of angle from left point
        while (!pq.isEmpty()) {
            Point vertex = pq.poll();
            int index = origIndexToSortedIndex[vertex.index];
            ans[vertex.index] = st.query(index, n-1);
            st.update(index, vertex.v);
        }
        for (int i = 0; i <= n-1; i++) pw.println(ans[i]);
    }

    static class Point{
        long x, y, v;
        int index;

        public Point(long x, long y, long v, int index) {
            this.x = x;
            this.y = y;
            this.v = v;
            this.index = index;
        }

        public String toString() {
            return "(index="+index+", x="+x+", y="+y+", value="+v+")";
        }
    }

    static class Comp implements Comparator<Point> {
        public int compare(Point p1, Point p2) {
            long val = cross(
                new long[] {p1.x, p1.y, 0},
                new long[] {p2.x, p2.y, 0}
            );
            if (val < 0) return -1;
            else return 1;
        }
    }

    static class Comp2 implements Comparator<Point> {
        public int compare(Point p1, Point p2) {
            long val = cross(
                new long[] {p1.x-dist, p1.y, 0},
                new long[] {p2.x-dist, p2.y, 0}
            );
            if (val < 0) return -1;
            else return 1;
        }
    }

    // takes the z-value of the cross product
    static long cross(long[] v1, long[] v2) {
        return v1[0]*v2[1] - v1[1]*v2[0];
    }

    static class SegmentTree {
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
        }

        public long query(int l, int r, int vertex, int vl, int vr) {
            if (l > vr || r < vl)
                return 0;
            if (vl >= l && vr <= r)
                return t[vertex];
            
            int vm = (vl + vr) / 2; // "vertex's left", "vertex's right", and "vertex's middle"
            return query(l, Math.min(r, vm), 2*vertex, vl, vm) + query(Math.max(l, vm+1), r, 2*vertex+1, vm+1, vr);
        }

        public long query(int l, int r) {
            // wrapper method
            return query(l, r, 1, 0, n-1);
        }

        public void update(int ind, long newVal, int vertex, int vl, int vr) {
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

        public void update(int ind, long newVal) {
            update(ind, newVal, 1, 0, n-1);
        }
    }
}
