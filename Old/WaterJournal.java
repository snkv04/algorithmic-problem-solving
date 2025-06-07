import java.util.*;
import java.io.*;

public class WaterJournal {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        solve();

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        String[] asdf = br.readLine().split(" ");
        int n = Integer.parseInt(asdf[0]), a = Integer.parseInt(asdf[1]), b = Integer.parseInt(asdf[2]);
        int min = Integer.MAX_VALUE, max = Integer.MIN_VALUE;
        for (int i = 1; i <= n-1; i++) {
            int num = Integer.parseInt(br.readLine());
            min = Math.min(min, num);
            max = Math.max(max, num);
        }
        if (a!=min && b!=max) pw.println(-1);
        else if (a!=min) pw.println(a);
        else if (b != max) pw.println(b);
        else {
            for (int i = a; i <= b; i++) pw.println(i);
        }
    }
}