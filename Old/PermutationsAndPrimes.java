import java.util.*;
import java.io.*;

public class PermutationsAndPrimes {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            if (n==1) {
                pw.println(1); continue;
            } else if (n==2) {
                pw.println("1 2"); continue;
            } else if (n==3) {
                pw.println("3 1 2");continue;
            }
            int[] a = new int[n];
            a[n/2]=1;
            a[0] = 2;
            a[n-1] = 3;
            int j = 4;
            for (int i = 0; i <= n-1; i++) {
                if (a[i]==0) {
                    a[i]=j;
                    j++;
                }
            }
            for (int num : a) pw.print(num + " ");
            pw.println();
        }

        br.close(); pw.close();
    }
}
