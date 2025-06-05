import java.util.*;
import java.io.*;

public class CoinCombinations2 {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        // what we want to do count all of the different *combinations* that add up
        // to x. in the previous problem, we counted all of the permutations, but in
        // this problem, we cannot have multiple permutations of the same combination
        // be counted, as that would be double counting and therefore be wrong in the
        // context of this problem; in other words, the difference between this problem
        // and the last problem is that in this one we want the number of distinct
        // unordered sequences (order doesn't matter), and in the other one we want the
        // number of distinct ordered sequences (where order does matter).
        // (in the problem, it says these in reverse, but that's actually wrong since in
        // this one we want to make sequences like 1+2+3 the same as 3+1+2, meaning the
        // sequences are like mathematical sets in that the order of their elements
        // does not matter. the previous problem wanted 1+2+3 and 3+1+2 to be different,
        // making the sequences like permutations as the order of the elements does
        // matter, meaning that they are ordered.)
        // so, how do we avoid double counting? in other words, how can we make it so
        // that there is only one permutation counted for each valid combination? one
        // way is to make sure that every sequence that adds up to a value in a subproblem
        // is in a nondescending order, so that for a sum like 6, the sequences
        // 3+2+1 or 2+1+3 are never counted and the only way to add to 6 using those
        // three numbers that is actually counted is 1+2+3. for this, we can sort
        // the coins into nondescending order and then, instead of looping through all
        // the coins for each sum up until x, we loop through all the subproblems up to
        // x for every coin. what this accomplishes is that now, since the coins are
        // only looped through once, the number of sequences that add up to each sum
        // in the array of memoized results only involves the sequences in nondescending
        // order (e.g. 1+1+1+1+2=6 and 1+1+2+2=6 would be counted, but not 1+2+1+2=6).
        // if printed, these sequences would all look like
        // c1+c1+c1+...+c2+c2+c2+c2+...+cn+cn+cn = sum, where there are just a bunch
        // of blocks of each coin. for each combination of coins, there is only the
        // permutation that looks like this, reducing the answer from the number of
        // permutations to the number of combinations. in fact, sorting the coins at
        // the beginning doesn't matter; we just have to loop through the coins on the
        // outer loop and the memoized results array on the inner loop, and by only
        // looping through the coins once the goal is reached.
        // the distinction between this and the alternative of doing the loops the other
        // way is that the other one counts all the different permutations as separate,
        // because we are repeatedly looping through all the coins for each subproblem
        // (circular reasoning?). also, the distinction between this and the knapsack
        // problem with weights and values is that in the latter, each coin can only be
        // used once at all for each sum/subproblem.
        // String[] line = br.readLine().split(" ");
        // int n = Integer.parseInt(line[0]);
        // int x = Integer.parseInt(line[1]);
        // int[] coins = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        // int[] memo = new int[x+1];
        // memo[0] = 1;
        // int mod = (int) (1e9 + 7);
        // for (int i = 0; i <= n-1; i++) {
        //     for (int j = 1; j <= x; j++) {
        //         if (j - coins[i] >= 0) {
        //             memo[j] += memo[j-coins[i]];
        //             memo[j] %= mod;
        //         }
        //     }
        // }
        // pw.print(memo[x]);

        // an alternative to this, which uses more memory space but may be more intuitive,
        // uses a 2D array memo[x][k] where the first variable is the sum we are adding up to
        // and the second variable denotes that we are using the first k coins (although a
        // potentially infinite amount of each of them). we can fill in this array by doing
        // each k one by one, in a very similar manner to the previous implementation, and
        // looping through all the sums for each coin. one thing to note, which might be
        // generalizable for later problems, is that the main variable that we loop upto
        // is the first axis of the n-dimensional array, and we loop through the other
        // variable/variables first (in the outer loop/loops), going through all of the
        // values on the first axis for each of these.
        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int x = Integer.parseInt(line[1]);
        int[] coins = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int[][] memo = new int[x+1][n+1];
        // for (int i = 0; i <= n; i++) memo[0][i] = 1;
        memo[0][0] = 1;
        int mod = (int) (1e9 + 7);
        for (int coin = 1; coin <= n; coin++) {
            for (int sum = 0; sum <= x; sum++) {
                memo[sum][coin] = memo[sum][coin-1];
                if (sum - coins[coin-1] >= 0) {
                    // memo[sum][coin] += memo[sum-coins[coin-1]][coin-1];

                    // the above line is incorrect and it took me some debugging to figure out why.
                    // the line above assumes that we are using each coin only once, since for each
                    // coin we only take the values from the previous coin's results. this would
                    // work for a knapsack problem where we can use each object once. the correct
                    // way (which btw is kind of a waste of using a 2D array, so 1D is probably
                    // simply objectively better) first copies the values from the previous coin's
                    // results, done above, and then uses the results from the current coin's
                    // previous sums (instead of using the results from the previous coin's previous
                    // sums). this way, we can use an infinite amount of each coin.

                    memo[sum][coin] += memo[sum-coins[coin-1]][coin];
                    memo[sum][coin] %= mod;
                }
            }
        }
        pw.println(memo[x][n]);
        // for (int i = 0; i <= x; i++) pw.println(Arrays.toString(memo[i]));

        br.close(); pw.close();
    }
}
