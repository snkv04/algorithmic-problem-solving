import java.util.*;
import java.io.*;

public class Promo {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int q = sc.nextInt();
        Integer[] p = new Integer[n];
        for (int i = 0; i <= n-1; i++) {
            p[i] = sc.nextInt();
        }
        Arrays.sort(p);
        long[] prefsums = new long[n+1];
        for (int i = 1; i <= n; i++) {
            prefsums[i] = prefsums[i-1] + p[i-1];
        }
        // pw.println(Arrays.toString(p));
        // pw.println(Arrays.toString(prefsums));

        while (q-->0) {
            int x = sc.nextInt();
            int y = sc.nextInt();
            pw.println(prefsums[n-x+y]-prefsums[n-x]);
        }

        sc.close(); pw.close();
    }
}
