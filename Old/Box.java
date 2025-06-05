import java.util.*;
import java.io.*;

public class Box {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            TreeSet<Integer> unused = new TreeSet<>();
            for (int j = 1; j <= n; j++) unused.add(j);
            int[] q = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            
            int[] p = new int[n];
            p[0] = q[0];
            unused.remove(p[0]);
            boolean works = true;
            for (int j = 1; j <= n-1; j++) {
                if (q[j] > q[j-1]) {
                    p[j] = q[j];
                    unused.remove(q[j]);
                } else {
                    if (unused.lower(q[j]) == null) {
                        works = false;
                        break;
                    } else {
                        p[j] = unused.lower(q[j]);
                        unused.remove(p[j]);
                    }
                }
            }

            if (works) {
                for (int j = 0; j <= n-1; j++) pw.print(p[j] + " ");
                pw.println();
            }
            else pw.println(-1);
        }

        br.close(); pw.close();
    }
}
