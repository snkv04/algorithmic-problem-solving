import java.util.*;
import java.io.*;

public class GridPaths {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        char[][] grid = new char[n][n];
        for (int i = 0; i <= n-1; i++) {
            grid[i] = br.readLine().toCharArray();
        }
        // for (char[] line : grid) pw.println(line);

        int[][] memo = new int[n][n];
        memo[0][0] = grid[0][0]=='*'?0:1;
        int mod = (int) (1e9+7);
        for (int i = 0; i <= n-1; i++) {
            for (int j = 0; j <= n-1; j++) {
                if (grid[i][j]=='*') continue;

                if (i-1>=0) {
                    memo[i][j] += memo[i-1][j];
                    memo[i][j] %= mod;
                }
                if (j-1>=0) {
                    memo[i][j] += memo[i][j-1];
                    memo[i][j] %= mod;
                }
            }
        }
        pw.print(memo[n-1][n-1]);

        br.close(); pw.close();
    }
}
