import java.util.*;
import java.io.*;

public class MakeEqualAgain {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        int n = Integer.parseInt(br.readLine());
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int pref = 0, suf = n-1;
        for (int i = 1; i <= n-1; i++) {
            if (a[i] == a[0]) pref = i;
            else break;
        }
        for (int i = n-2; i >= 0; i--) {
            if (a[i] == a[n-1]) suf = i;
            else break;
        }

        if (suf <= pref) {
            pw.println(0);
        } else if (a[0] == a[n-1]) {
            pw.println(suf-1-pref);
        } else {
            pw.println(Math.min(n-1-pref, suf));
        }
    }
}