import java.util.*;
import java.io.*;

public class SumInBinaryTree {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        while (t-- > 0) {
            long n = sc.nextLong();
            long ans = 0;
            while (n >= 1) {
                ans += n;
                n /= 2;
            }
            pw.println(ans);
        }

        sc.close(); pw.close();
    }
}
