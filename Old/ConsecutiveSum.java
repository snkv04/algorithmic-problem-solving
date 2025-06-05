import java.util.*;
import java.io.*;

public class ConsecutiveSum {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        long[] s = new long[t];
        for (int i = 1; i <= t; i++) {
            int[] line = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int n = line[0];
            int k = line[1];
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            for (int j = k; j <= a.length - 1; j++) {
                if (a[j] > a[j % k]) {
                    a[j % k] = a[j];
                }
            }

            long sum = 0;
            for (int j = 0; j <= k - 1; j++) {
                sum += a[j];
            }
            pw.println(sum);
        }

        br.close(); pw.close();
    }
}
