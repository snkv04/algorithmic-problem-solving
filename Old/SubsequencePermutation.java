import java.util.*;
import java.io.*;

public class SubsequencePermutation {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            char[] string = br.readLine().toCharArray();
            char[] sorted = Arrays.copyOf(string, n);
            Arrays.sort(sorted);
            int ans = 0;
            for (int j = 0; j <= string.length-1; j++) {
                if (string[j]!=sorted[j])ans++;
            }
            pw.println(ans);
        }

        br.close(); pw.close();
    }
}
