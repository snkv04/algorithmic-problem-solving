import java.io.*;

public class LevenshteinDistance {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.println(minDistance(br.readLine(), br.readLine()));
    }

    public static int minDistance(String word1, String word2) {
        char[] a = word1.toCharArray();
        char[] b = word2.toCharArray();
        int[][] memo = new int[a.length+1][b.length+1];
        for (int i=1;i<=a.length;i++) memo[i][0] = i;
        for (int i=1;i<=b.length;i++) memo[0][i] = i;
        for (int i = 1; i <= a.length; i++) {
            for (int j = 1; j <= b.length; j++) {
                memo[i][j] = Math.min(memo[i][j-1], memo[i-1][j]) + 1;
                if (a[i-1]==b[j-1])
                    memo[i][j] = Math.min(memo[i][j], memo[i-1][j-1]);
                else
                    memo[i][j] = Math.min(memo[i][j], memo[i-1][j-1]+1);
            }
        }
        return memo[a.length][b.length];
    }
}