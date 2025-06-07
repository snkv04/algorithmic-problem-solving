import java.util.*;
import java.io.*;

public class TwoLetterStrings {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[][] numStrings = new int[11][11];
            for (int i = 1; i <= n; i++) {
                String s = br.readLine();
                int a = s.charAt(0)-'a';
                int b = s.charAt(1)-'a';
                numStrings[a][b]++;
            }

            long ans = 0;
            for (int i = 0; i <= 10; i++) {
                for (int j = 0; j <= 10; j++) {
                    long count = 0;
                    for (int hor = 0; hor <= 10; hor++) {
                        if (hor != j)
                            count += numStrings[i][hor];
                    }
                    for (int vert = 0; vert <= 10; vert++) {
                        if (vert != i) count += numStrings[vert][j];
                    }
                    ans += count * numStrings[i][j];
                }
            }
            pw.println(ans/2);
        }

        br.close(); pw.close();
    }
}
