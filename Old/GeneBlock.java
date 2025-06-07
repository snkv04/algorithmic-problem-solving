import java.util.*;
import java.io.*;

public class GeneBlock {
    static BufferedReader br;
    static PrintWriter pw;
    static int[] modToCount;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        modToCount = new int[10];
        for (int i = 1; i <= 10; i++) {
            modToCount[(7*i)%10] = i;
        }

        int t = Integer.parseInt(br.readLine()); // 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        int n = Integer.parseInt(br.readLine()), mod = n % 10;
        if (n < modToCount[mod] * 7) {
            pw.println(-1);
        } else {
            pw.println(modToCount[mod]);
        }
    }
}
