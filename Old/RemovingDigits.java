import java.util.*;
import java.io.*;

public class RemovingDigits {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[] memo = new int[n+1];
        for (int i = 1; i <= n; i++) {
            int val = i;
            int rightmostDigit = 0;
            memo[i] = Integer.MAX_VALUE;
            while (val > 0) {
                rightmostDigit = val % 10;
                val /= 10;
                if (rightmostDigit != 0)
                    memo[i] = Math.min(memo[i], memo[i-rightmostDigit]+1);
            }
        }
        pw.println(memo[n]);

        br.close(); pw.close();
    }
}
