import java.util.*;
import java.io.*;

public class HoofPaperScissorsGold {
    public static void main(String[] args) throws IOException {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("hps.in"));
        PrintWriter pw = new PrintWriter(new FileWriter("hps.out"));

        String[] line =  br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int k = Integer.parseInt(line[1]);
        char[] moves = new char[n];
        for (int i = 0; i <= n-1; i++) moves[i] = br.readLine().charAt(0);

        int[][][] memo = new int[n+1][3][k+1];
        char[] options = {'H', 'P', 'S'};
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= 2; j++) {
                memo[i][j][0] = memo[i-1][j][0] + game(options[j], moves[i-1]);
            }
        }

        for (int i = 1; i <= n; i++) { // current game
            for (int j = 0; j <= 2; j++) { // current move
                for (int changes = 1; changes <= k; changes++) { // number of switches made so far
                    memo[i][j][changes] = Math.max(
                        Math.max(memo[i-1][j][changes], memo[i-1][j][changes-1]),
                        Math.max(memo[i-1][(j+1)%3][changes-1], memo[i-1][(j+2)%3][changes-1])
                    ) + game(options[j], moves[i-1]);
                }
            }
        }
        pw.print(Math.max(memo[n][0][k], Math.max(memo[n][1][k], memo[n][2][k])));

        br.close(); pw.close();

        // this way, dp[i][j][k] denotes the maximum number of wins at game i, choosing
        // move j (using the map from {0,1,2} to {h, p, s}), and having done AT MOST k changes
        // of moves. an alternative would be to make memo[i][j][k] equal to the maximum number
        // of wins at game i, choosing move j, and having done exactly k changes. however, this
        // would require the final answer to iterate over all of the values of the form
        // memo[n][j][moves], where 0≤j≤2, 0≤moves≤k. this would mean taking the max of k*3 values.
        // this is not necessarily worse; it's just a matter of preference.
    }

    static int game(char bessie, char fj) {
        if (bessie=='H'&&fj=='S' || bessie=='P'&&fj=='H' ||  bessie=='S'&&fj=='P')
            return 1;
        else return 0;
    }
}
