import java.util.*;
import java.io.*;

public class SumOfOddIntegers {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        for (int i = 1; i <= t; i++) {
            int n = sc.nextInt();
            int k = sc.nextInt();
            int odd = 1;
            while (k > 1 && n > 0) {
                n-=odd;
                odd+=2;
                k--;
            }
            if (n%2==1 && n >= odd) {
                pw.println("YES");
            } else pw.println("NO");
        }

        sc.close(); pw.close();
    }
}
