import java.util.*;
import java.io.*;

public class DivisibilityByEight {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        char[] n = br.readLine().toCharArray();
        // memo[i][j] represents if it is possible to make a number where dividing it by
        // 8 gives remainder j using some of the first i digits
        boolean[][] memo = new boolean[n.length+1][8];
        boolean works = false;
        // prev[i][j] denotes the value (between 0 and 7, inclusive) from the previous layer
        // of the memo array which the result memo[i][j] comes from
        int[][] prev = new int[n.length+1][8];
        int ansi = -1;
        for (int i = 1; i <= n.length; i++) {
            int currDigit = n[i-1]-'0';
            for (int j = 0; j <= 7; j++) {
                // not using this digit
                if (memo[i-1][j]) memo[i][j] = true;
                prev[i][j] = j;
            }

            // using this digit only (meaning it will be the leftmost digit of future number strings
            // involving this digit, if this option is used later)
            memo[i][currDigit%8] = true;
            prev[i][currDigit%8] = -1;

            for (int j = 0; j <= 7; j++) {
                // using this digit in addition to whatever previous sequence resulted in the
                // previous digit's memo to be true for some j
                int addingCurrentDigit = j*10 + currDigit;
                if (memo[i-1][j] && !memo[i][addingCurrentDigit%8]) {
                    memo[i][addingCurrentDigit%8] = true;;
                    prev[i][addingCurrentDigit%8] = j;
                }
            }
            
            if (memo[i][0]==true) {
                works = true;
                ansi = i;
                break;
            }
        }
        if (!works) pw.println("NO");
        else {
            Stack<Character> s = new Stack<>();
            int i = ansi;
            int j = 0;
            while (i > 0 && prev[i][j]!=-1) {
                if (prev[i][j] != j) {
                    s.add(n[i-1]);
                }
                j = prev[i][j];
                i--;
            }

            if (i>0 && prev[i][j]==-1) s.add(n[i-1]);
            
            pw.println("YES");
            while (!s.isEmpty()) pw.print(s.pop());
        }

        br.close(); pw.close();
    }
}
