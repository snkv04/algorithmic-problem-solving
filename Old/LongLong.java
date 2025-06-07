import java.util.*;
import java.io.*;

public class LongLong {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int segments = 0;
            boolean flipping = false;
            long ans = 0;
            for (int i = 0; i <= n-1; i++) {
                if (flipping) {
                    if (a[i] > 0) {
                        ans += a[i];
                        flipping = false;
                    } else {
                        ans += -a[i];
                    }
                } else {
                    if (a[i] < 0) {
                        flipping = true;
                        segments++;
                        ans += -a[i];
                    } else {
                        ans += a[i];
                    }
                }
            }
            pw.println(ans + " "+ segments);
        }

        br.close(); pw.close();
    }
}
