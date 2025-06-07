import java.util.*;
import java.io.*;

public class IncreasingSubsequences {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static int[] di = {0, 0, 1, -1}, dj = {1, -1, 0, 0};

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine()); // 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        long x = Long.parseLong(br.readLine());
        ArrayList<Integer> a = new ArrayList<>();
        a.add(1);
        long soFar = 2;
        int curr = 1;
        while (soFar < x) {
            if (soFar + ((long)1 << curr) <= x) {
                soFar += ((long)1 << curr);
                a.add(++curr);
            } else {
                curr--;
            }
        }
        // pw.println(a);

        pw.println(a.size());
        for (long num : a) pw.print(num+" ");
        pw.println();
    }
}
