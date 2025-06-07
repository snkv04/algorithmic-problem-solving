import java.util.*;
import java.io.*;

public class DynamicRangeSumQueries {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int q = Integer.parseInt(line[1]);
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        SegmentTree st = new SegmentTree(a);
        for (int i = 1; i <= q; i++) {
            line = br.readLine().split(" ");
            if (Integer.parseInt(line[0]) == 1) {
                int k = Integer.parseInt(line[1]) - 1;
                int u = Integer.parseInt(line[2]);
                st.update(k, u);
            } else {
                int l = Integer.parseInt(line[1]) - 1;
                int r = Integer.parseInt(line[2]) - 1;
                pw.println(st.query(l, r));
            }
        }

        br.close(); pw.close();
    }

    static class SegmentTree {
        long[] f;
        int n;

        public SegmentTree(int[] original) {
            n = original.length;
            f = new long[4*n];

            build(original, 1, 0, n-1);
        }

        public void build(int[] a, int node, int tmpL, int tmpR) {
            if (tmpL == tmpR) {
                f[node] = a[tmpL];
            } else {
                int tmpM = (tmpL + tmpR) / 2;
                build(a, 2*node, tmpL, tmpM);
                build(a, 2*node+1, tmpM+1, tmpR);
                f[node] = f[2*node] + f[2*node+1]; // computes the higher-level node afterward
            }
        }

        public long query(int l, int r, int node, int tmpL, int tmpR) {
            if (l > r)
                return 0;
            if (tmpL == l && tmpR == r)
                return f[node];
            
            int tmpM = (tmpL + tmpR) / 2; // "temporary left", "temporary right", and "temporary mid"
            return query(l, Math.min(r, tmpM), 2*node, tmpL, tmpM)
                + query(Math.max(l, tmpM+1), r, 2*node+1, tmpM+1, tmpR);
        }

        public long query(int l, int r) {
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
                f[node] = f[2*node] + f[2*node+1];
            }
        }

        public void update(int ind, int newVal) {
            update(ind, newVal, 1, 0, n-1);
        }
    }
}
