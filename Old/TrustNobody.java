import java.util.*;
import java.io.*;

public class TrustNobody {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        while (t-->0) {
            int n = sc.nextInt();
            Integer[] a = new Integer[n];
            for (int i = 0; i < n; i++) a[i] = sc.nextInt();
            Arrays.sort(a);

            if (a[0]==n) {
                pw.println(-1);
                continue;
            } else if (a[0] > n) {
                pw.println(n);
                continue;
            } else if (a[n-1]==0) {
                pw.println(0);
                continue;
            }
            int ans = -1;
            for (int i = 1; i <= n-1; i++) {
                if (a[n-i] > i && i >= a[n-i-1]) {
                    ans = i;
                    break;
                }
            }
            pw.println(ans);
        }

        sc.close(); pw.close();
    }
}
