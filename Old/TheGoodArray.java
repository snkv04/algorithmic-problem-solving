import java.util.*;
import java.io.*;

public class TheGoodArray {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        while (t-->0) {
            int n = sc.nextInt();
            int k = sc.nextInt();
            int i = 0;
            int ans = 0;
            while (i <= n-1) {
                i += k;
                ans++;
            }
            if (i != n-1 + k) ans++;
            pw.println(ans);
        }

        sc.close(); pw.close();
    }
}
