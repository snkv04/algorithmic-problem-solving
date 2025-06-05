import java.util.*;
import java.io.*;

public class BookShop {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int x = sc.nextInt();
        int[] weights = new int[n];
        for (int i = 0; i <= n-1; i++) weights[i] = sc.nextInt();
        int[] values = new int[n];
        for (int i = 0; i <= n-1; i++) values[i] = sc.nextInt();

        // int[][] memo = new int[x+1][n+1];
        // // memo[i][j] is the maximum value with weights summing up to i using the first j objects
        // for (int j = 1; j <= n; j++) {
        //     for (int i = 0; i <= x; i++) {
        //         // currently using the book j-1
        //         memo[i][j] = memo[i][j-1];
        //         if (i - weights[j-1] >= 0) {
        //             memo[i][j] = Math.max(memo[i][j], memo[i-weights[j-1]][j-1] + values[j-1]);
        //         }
        //     }
        // }
        // pw.println(memo[x][n]);

        int[] memo = new int[x+1];
        for (int j = 0; j <= n-1; j++) {
            for (int i = x; i >= 0; i--) { // go in reverse order of sums to avoid using the current book twice
                if (i-weights[j] >= 0) {
                    // chooses whether or not to use the current book in order to maximize
                    // the value. if not using it, then the max value of the current weight
                    // remains the same. if using it, then we look at the max value of
                    // (current weight - weight of current book), and then add the value of
                    // the current book to it.
                    memo[i] = Math.max(memo[i], memo[i-weights[j]] + values[j]);
                }
            }
        }
        pw.println(memo[x]);

        sc.close(); pw.close();
    }
}
