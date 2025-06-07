import java.util.*;
import java.io.*;

public class NoPrimeDifferences {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        for (int i = 1; i <= t; i++) {
            int n = sc.nextInt();
            int m = sc.nextInt();
            for (int j = n/2; j <= (n/2)*2-1; j++) {
                for (int k = j*m+1; k <= j*m+m; k++) {
                    pw.print(k+" ");
                }
                pw.println();
                for (int k = (j-n/2)*m+1; k <= (j-n/2)*m+m; k++) {
                    pw.print(k+" ");
                }
                pw.println();
            }
            if (n%2==1) {
                for (int k = (n-1)*m+1; k <= (n-1)*m+m; k++) {
                    pw.print(k+" ");
                }
                pw.println();
            }
        }

        sc.close(); pw.close();

        // doing alternating rows in a 5 1 6 2 7 3 8 4 9 pattern ensures that
        // horizontal differences are 1 and vertical differences are at least
        // multiples of 2
    }
}