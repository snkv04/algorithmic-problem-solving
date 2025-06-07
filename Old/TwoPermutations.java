import java.util.*;
import java.io.*;

public class TwoPermutations {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        for (int i = 1; i <= t; i++) {
            int n = sc.nextInt();
            int a = sc.nextInt();
            int b = sc.nextInt();
            boolean works = a + b <= n-2 || (a == n && b == n);
            pw.println(works ? "yes" : "no");
        }

        sc.close(); pw.close();
    }
}
