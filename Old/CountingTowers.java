import java.util.*;
import java.io.*;

public class CountingTowers {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        long[] split = new long[1000000];
        long[] together = new long[1000000];
        long[] memo = new long[1000000];
        split[0]=1;
        together[0]=1;
        memo[0] = 2;
        int mod = (int) (1e9+7);
        for (int i = 1; i <= 999999; i++) {
            split[i] = 4 * split[i-1] + together[i-1];
            split[i] %= mod;
            together[i] = 2 * together[i-1] + split[i-1];
            together[i] %= mod;
            memo[i] = split[i]+together[i];
            memo[i] %= mod;
        }
        for (int test = 1; test <= t; test++) {
            int n = sc.nextInt();
            pw.println(memo[n-1]);
        }

        sc.close(); pw.close();

        // first look at the most recent subproblem and look at all the ways it connects
        // to the previous subproblem. there are eight possibilities:
        // _____   _____   _____   _____   _____   _____   _____   _____
        // |_|_|   | |_|   |_| |   | | |   |_|_|   |___|   |___|   |   |
        // |_|_|   |_|_|   |_|_|   |_|_|   |___|   |_|_|   |___|   |___|
        //
        // five of them have the most recent (top) layer split, and three of them have it
        // together. in connecting to the previous layer, it can either be completely separate,
        // where they don't interact, or "connect" (share a box) in some pattern. so, the
        // number of combinations per layer that are counting if the top layer is split and
        // that of the top layer being together can be memoized separately, and the answer
        // just sums them up.
    }
}
