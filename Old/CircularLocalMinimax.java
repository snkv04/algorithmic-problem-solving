import java.util.*;
import java.io.*;

public class CircularLocalMinimax {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        while (t-- > 0) {
            int n = sc.nextInt();
            Integer[] a = new Integer[n];
            for (int i = 0; i <= n-1; i++) a[i] = sc.nextInt();
            Arrays.sort(a);
            if (n%2==1) {
                pw.println("NO");
                continue;
            }

            int[] ans = new int[n];
            for (int i = 0; i <= n/2 - 1; i++) {
                ans[2*i] = a[i];
                ans[2*i+1] = a[i + n/2];
            }
            boolean works = true;
            for (int i = 0; i <= n-1; i++) {
                if (ans[i]==ans[(i+1)%n]) {
                    works = false;
                    break;
                }
            }
            if (!works) {
                pw.println("NO");
                continue;
            }
            pw.println("YES");
            for (int num : ans) pw.print(num + " ");
            pw.println();
        }

        sc.close(); pw.close();
    }
}
