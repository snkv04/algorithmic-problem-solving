import java.util.*;
import java.io.*;

public class StandUpComedian {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            if (a[0] == 0) {
                pw.println(1);
                continue;
            }

            int count = a[0];
            count += Math.min(a[1], a[2]) * 2;
            int remainder = a[1] - Math.min(a[1], a[2]);
            remainder = Math.max(remainder, a[2] - Math.min(a[1], a[2]));
            count += Math.min(a[0] + 1, remainder + a[3]);
            pw.println(count);
        }

        br.close(); pw.close();
    }
}
