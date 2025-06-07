import java.util.*;
import java.io.*;

public class DifferentialSorting {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            if (a[n-1] < a[n-2]) {
                pw.println(-1);
                continue;
            } else if (a[n-1] < 0) {
                int[] b = Arrays.copyOf(a, n);
                Arrays.sort(b);
                boolean sorted = true;
                for (int i = 0; i<=n-1; i++) {
                    if (b[i]!=a[i]) {
                        sorted = false;
                        break;
                    }
                }
                pw.println(sorted?0:-1);
            } else {
                pw.println(n-2);
                for (int i = 1; i <= n-2; i++) {
                    pw.println(i + " " + (n-1) + " " + n);
                }
            }
        }

        br.close(); pw.close();
    }
}
