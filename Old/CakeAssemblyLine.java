import java.util.*;
import java.io.*;

public class CakeAssemblyLine {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] asdf = br.readLine().split(" ");
            int n = Integer.parseInt(asdf[0]), w = Integer.parseInt(asdf[1]), h = Integer.parseInt(asdf[2]);
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int[] b = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int[] lc = new int[n], rc = new int[n], ld = new int[n], rd = new int[n];
            for (int i = 0; i <= n-1; i++) {
                lc[i] = a[i] - w;
                rc[i] = a[i]+w;
                ld[i] = b[i]-h;
                rd[i] = b[i]+h;
            }

            int mr = Integer.MAX_VALUE, // the most to the right side that any cake's left side can be
                ml = Integer.MIN_VALUE; // the most to the left side that any cake's right side can be
            for (int i = 0; i <= n-1; i++) {
                mr = Math.min(mr, ld[i]-lc[i]);
                ml = Math.max(ml, rd[i]-rc[i]);
            }
            pw.println(mr >= ml ? "YES" : "NO");
        }

        br.close(); pw.close();
    }
}
