import java.util.*;
import java.io.*;

public class HamonOdyssey {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            long last = a[0];
            int ans = 0;
            if (a[0] == 0) { ans++; last = (1<<30) - 1; }
            // every AND will make it decrease, but it can't decrease more than
            // decreasing to 0
            for (int i = 1; i <= n-1; i++) {
                if ((a[i] & last) == 0) {
                    ans++;
                    last = (1<<30) - 1;
                } else {
                    last = last & a[i];
                }
            }
            if (ans == 0) ans++;
            pw.println(ans);
        }

        br.close(); pw.close();
    }
}
