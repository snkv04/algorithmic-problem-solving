import java.util.*;
import java.io.*;

public class RunningMiles {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-- > 0) {
            int n = Integer.parseInt(br.readLine());
            int[] b = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int[][] memo = new int[n+1][3];
            for (int i = 0; i <= 2; i++) memo[0][i] = Integer.MIN_VALUE;
            for (int i = 1; i <= n; i++) {
                memo[i][0] = Math.max(memo[i-1][0], b[i-1]+i);
                memo[i][1] = Math.max(memo[i-1][1], memo[i-1][0] + b[i-1]);
                memo[i][2] = Math.max(memo[i-1][2], memo[i-1][1] + b[i-1] - i);
            }
            pw.println(memo[n][2]);
        }

        br.close(); pw.close();

        // the first intuitive guess would be to pick the largest 3 elements in the array,
        // but this fails because there could be very large distances between them. then a DP
        // solution comes to mind where we look at each sight in order and either decide to have
        // that be the end of the 3 sights or not. (by the way, the interval of sights will start
        // on the left sight, not anywhere before, and end on the last sight, not anywhere after,
        // to not add unnecessary distance. actually, this is already said in the problem, so
        // nvm.) the reason why this solution doesn't work is because the previous two sights
        // are not optimized. so, the correct solution goes through each sight and either uses it
        // or doesn't use it for each of the 3 sight "types" (first one, middle one, or last one).
        // this is guaranteed to be more thorough, and correct. also, doing this makes it so
        // that the maximum value if using the first overall sight as sight M or R is infinitely
        // negative (or at least effectively), and the same for using the second sight overall
        // as sight R, and this serves as a sanity check because it is the way it should be
        // (since those cases make no sense). also, btw, this solution splits up the expression
        // "b_l + b_m + b_r - (r-l)" into "(b_l + l) + b_m + (b_r - r)" to make the individual
        // parts of computation for dynamic programming easier to compute.
    }

    // // // //

    static class Multiset {
        TreeMap<Integer, Integer> mset = new TreeMap<>();

        public void add(int x) {
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + 1);
            } else {
                mset.put(x, 1);
            }
        }
        
        public void remove(int x) {
            mset.put(x, mset.get(x) - 1);
            if (mset.get(x) == 0) mset.remove(x);
        }

        public void add(int x, int q) {
            // q for quantity
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + q);
            } else {
                mset.put(x, q);
            }
        }
    }
}
