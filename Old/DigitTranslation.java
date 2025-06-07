import java.util.*;
import java.io.*;

public class DigitTranslation {
    static BufferedReader br;
    static PrintWriter pw;
    static char[] s;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        solve();

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        String[] toLetters = new String[10];
        toLetters[0] = "zero";
        toLetters[1] = "one";
        toLetters[2] = "two";
        toLetters[3] = "three";
        toLetters[4] = "four";
        toLetters[5] = "five";
        toLetters[6] = "six";
        toLetters[7] = "seven";
        toLetters[8] = "eight";
        toLetters[9] = "nine";

        s = br.readLine().toCharArray();
        int n = s.length;
        int[] memo = new int[n+1], ways = new int[n+1];
        ways[0] = 1;
        for (int i = 1; i <= n; i++) {
            int minPossible = memo[i-1] + 1;
            for (int j = 0; j <= 9; j++) {
                String asWord = toLetters[j];
                if (!match(i-1, asWord)) continue;
                minPossible = Math.min(minPossible, memo[i-asWord.length()]+1);
                break;
            }

            int numWays = 0;
            if (minPossible == memo[i-1] + 1) numWays = ways[i-1];
            for (int j = 0; j <= 9; j++) {
                String asWord = toLetters[j];
                if (!match(i-1, asWord)) continue;
                if (minPossible == memo[i-asWord.length()]+1) numWays += ways[i-asWord.length()];
                break;
            }
            memo[i] = minPossible;
            ways[i] = numWays % 9302023;
        }
        // pw.println(Arrays.toString(memo));
        // pw.println(Arrays.toString(ways));
        pw.println(memo[n]);
        pw.println(ways[n]);
    }

    static boolean match(int zeroIndex, String number) {
        if (zeroIndex < number.length() - 1) return false;
        int start = zeroIndex - number.length() + 1;
        for (int i = 0; i <= number.length() - 1; i++) {
            if (s[start+i] != number.charAt(i)) return false;
        }
        return true;
    }
}