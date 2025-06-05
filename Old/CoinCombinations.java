import java.util.*;
import java.io.*;

public class CoinCombinations {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int x = Integer.parseInt(line[1]);
        int[] coins = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int[] memo = new int[x+1];
        memo[0] = 1;
        for (int i = 1; i <= x; i++) {
            for (int j = 0; j <= n-1; j++) {
                if (i - coins[j] >= 0) {
                    memo[i] += memo[i-coins[j]];
                    memo[i] %= (int) (1e9+7);
                }
            }
        }
        pw.print(memo[x]);

        br.close(); pw.close();
    }
}
