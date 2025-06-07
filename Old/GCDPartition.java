import java.util.*;
import java.io.*;

public class GCDPartition {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            long[] prefsums = new long[n], sufsums = new long[n];
            prefsums[0] = a[0];
            for (int i = 1; i <= n-1; i++) {
                prefsums[i] = prefsums[i-1] + a[i];
            }
            sufsums[n-1] = a[n-1];
            for (int i = n-2; i >= 0; i--) {
                sufsums[i] = sufsums[i+1] + a[i];
            }
            
            long max = 0;
            for (int i = 0; i <= n-2; i++) {
                long x = prefsums[i];
                long y = sufsums[i+1];
                max = Math.max(max, gcd(Math.max(x, y), Math.min(x, y)));
            }
            pw.println(max);
        }

        br.close(); pw.close();

        // if several segments of the array all have some common gcd, then combining multiple
        // segments cannot decrease the GCD (and may increase it), since the sum of the combined
        // segment would be a multiple of the sum of each of the segments being combined. that
        // is the key observation. so we only use 2 segments, and use prefix/suffix sums to find
        // the best split.
    }

    static long gcd(long a, long b) {
        while (b != 0) {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
}
