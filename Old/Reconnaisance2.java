import java.util.*;
import java.io.*;

public class Reconnaisance2 {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int[] a = new int[n];
        for (int i = 0; i <= n-1; i++) {
            a[i] = sc.nextInt();
        }
        int first = 0;
        int second = 1;
        int last = Math.abs(a[1]-a[0]);
        for (int i = 2; i <= n; i++) {
            if (Math.abs(a[(i)%n]-a[(i-1)%n]) < last) {
                last = Math.abs(a[i%n]-a[(i-1)%n]);
                first = i-1;
                second = i%n;
            }
        }
        pw.println((first+1) + " " + (second+1));

        sc.close(); pw.close();
    }
}
