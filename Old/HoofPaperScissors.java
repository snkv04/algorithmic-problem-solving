import java.util.*;
import java.io.*;

public class HoofPaperScissors {
    public static void main(String[] args) throws Exception {
        // BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter pw = new PrintWriter(System.out);
        BufferedReader br = new BufferedReader(new FileReader("hps.in"));
        PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter("hps.out")));

        int n = Integer.parseInt(br.readLine());
        char[] moves = new char[n];
        for (int i = 0; i <= n-1; i++) {
            moves[i] = br.readLine().charAt(0);
        }

        // 0 is if Bessie picks H, 1 is P, 2 is S
        int[][] prefix = new int[3][n];
        prefix[0][0] = hps('H', moves[0]);
        prefix[1][0] = hps('P', moves[0]);
        prefix[2][0] = hps('S', moves[0]);
        for (int i = 1; i <= n-1; i++) {
            prefix[0][i] = prefix[0][i-1] + hps('H', moves[i]);
            prefix[1][i] = prefix[1][i-1] + hps('P', moves[i]);
            prefix[2][i] = prefix[2][i-1] + hps('S', moves[i]);
        }
        int[][] suffix = new int[3][n];
        suffix[0][n-1] = hps('H', moves[n-1]);
        suffix[1][n-1] = hps('P', moves[n-1]);
        suffix[2][n-1] = hps('S', moves[n-1]);
        for (int i = n-2; i >= 0; i--) {
            suffix[0][i] = suffix[0][i+1] + hps('H', moves[i]);
            suffix[1][i] = suffix[1][i+1] + hps('P', moves[i]);
            suffix[2][i] = suffix[2][i+1] + hps('S', moves[i]);
        }

        // for (int[] arr:prefix)pw.println(Arrays.toString(arr));
        // pw.println();
        // for (int[] arr:suffix)pw.println(Arrays.toString(arr));
        // pw.println();

        // the prefix and suffix sum over the whole array is the same,
        // so only have to check that once
        // actually, don't have to check that at all, because during the
        // scan, if we check the corresponding prefix and suffix of the
        // same move type, then we get the number of games won if playing
        // that move the whole time
        int maxWins = -1;
        for (int i = 0; i <= n-2; i++) {
            for (int j = 0; j <= 2; j++) {
                for (int k = 0; k <= 2; k++) {
                    maxWins = Math.max(maxWins, prefix[j][i] + suffix[k][i+1]);
                }
            }
        }
        pw.print(maxWins);

        br.close(); pw.close();
    }

    static int hps(char bess, char john) {
        // returns true if bessie wins, false if tie or lose
        if ((bess=='H'&&john=='S') || (bess=='P'&&john=='H') || (bess=='S'&&john=='P'))
            return 1;
        else return 0;
    }
}
