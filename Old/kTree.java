import java.util.*;
import java.io.*;

public class kTree {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int k = Integer.parseInt(line[1]);
        int d = Integer.parseInt(line[2]);
        int[][] memo = new int[n+1][2];
        memo[0][0] = 1;
        int mod = (int) 1e9+7;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= Math.min(k, i); j++) {
                if (j < d) {
                    memo[i][0] += memo[i-j][0];
                    memo[i][0] %= mod;
                    memo[i][1] += memo[i-j][1];
                    memo[i][1] %= mod;
                } else {
                    memo[i][1] += memo[i-j][1];
                    memo[i][1] %= mod;
                    memo[i][1] += memo[i-j][0];
                    memo[i][1] %= mod;
                }
            }
        }
        pw.print(memo[n][1]);

        br.close(); pw.close();
    }
}
