import java.util.*;
import java.io.*;

public class MinimizingCoins {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int x = Integer.parseInt(line[1]);
        int[] c = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        long[] dp = new long[x+1];
        dp[0] = 0;
        for (int i = 1; i <= x; i++) {
            dp[i] = (long) Integer.MAX_VALUE;
            for (int j = 0; j <= n-1; j++) {
                if (i-c[j] >= 0) {
                    dp[i] = Math.min(dp[i - c[j]] + 1, dp[i]);
                }
            }
        }
        pw.println(dp[x]==Integer.MAX_VALUE ? -1 : dp[x]);

        br.close(); pw.close();
    }
}
