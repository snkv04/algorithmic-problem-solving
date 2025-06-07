import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class RhythmFlow {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static int[] di = {0, 0, 1, -1}, dj = {1, -1, 0, 0};

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        String[] s = br.readLine().split(" ");
        int n = Integer.parseInt(s[0]), m = Integer.parseInt(s[1]);
        int[] expected = new int[n+1];
        for (int i = 1; i <= n; i++) {
            expected[i] = Integer.parseInt(br.readLine());
        }
        int[] actual = new int[m+1];
        for (int i = 1; i <= m; i++) {
            actual[i] = Integer.parseInt(br.readLine());
        }

        int[][] dp = new int[n+1][m+1];
        // int ans = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                dp[i][j] = Math.max(Math.max(dp[i][j-1], dp[i-1][j]), dp[i-1][j-1] + connect(expected[i], actual[j]));
                // ans = Math.max(ans, dp[i][j]);
            }
        }
        // for (int i = 0; i <= n; i++) {
        //     pw.println("dp["+i+"] =\t"+Arrays.toString(dp[i]));
        // }
        // pw.println(ans);
        pw.println(dp[n][m]);
    }

    static int connect(int expected, int actual) {
        int diff = Math.abs(expected-actual);
        if (diff <= 15) return 7;
        if (diff <= 23) return 6;
        if (diff <= 43) return 4;
        if (diff <= 102) return 2;
        return 0;
    }
}
