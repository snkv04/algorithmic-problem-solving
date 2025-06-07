import java.util.*;
import java.io.*;

public class DiceCombinations {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[] dp = new int[n+1];
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= 6; j++) {
                if (i-j>=0) {
                    dp[i] += dp[i-j];
                    dp[i] %= 1e9 + 7;
                }
            }
        }
        // pw.println(10e9+7);
        pw.print(dp[n]);

        br.close(); pw.close();
    }
}
