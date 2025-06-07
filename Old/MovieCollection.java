import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class MovieCollection {
    static BufferedReader br;
    static PrintWriter pw;

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
        String[] split = br.readLine().split(" ");
        int m = Integer.parseInt(split[0]), r = Integer.parseInt(split[1]);
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        HashMap<Integer, Integer> toIdx = new HashMap<>();
        SegmentTree st = new SegmentTree(new int[m+r]);
        for (int i = 0; i <= m-1; i++) {
            toIdx.put(i, m-1-i);
            st.update(m-1-i, 1);
        }

        for (int i = 0; i <= r-1; i++) {
            int movie = a[i] - 1;
            pw.print(st.query(toIdx.get(movie)+1, m+r-1)+" ");
            st.update(toIdx.get(movie), 0);
            toIdx.put(movie, m+i);
            st.update(m+i, 1);
        }
        pw.println();
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
                t[vertex] = t[2*vertex] + t[2*vertex+1];
            }
        }

        // l and r are the bounds of the query; vl and vr are the bounds of the current vertex
        public long query(int l, int r, int vertex, int vl, int vr) {
            if (l > r)
                return 0;
            if (vl == l && vr == r)
                return t[vertex];
            
            int vm = (vl + vr) / 2;
            return query(l, Math.min(r, vm), 2*vertex, vl, vm) + query(Math.max(l, vm+1), r, 2*vertex+1, vm+1, vr);
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
                t[vertex] = t[2*vertex] + t[2*vertex+1];
            }
        }

        public void update(int ind, int newVal) {
            update(ind, newVal, 1, 0, n-1);
        }
    }
}
