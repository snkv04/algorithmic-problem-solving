import java.util.*;
import java.io.*;

public class SportMafia {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        long n = sc.nextInt();
        long k = sc.nextInt();
        // int adding = 1;
        long box = 0;
        for (long i = 1; i <= n; i++) {
            box += i;
            if (box - k == n - i) {
                pw.println(n-i);
                break;
            }
        }

        sc.close(); pw.close();
    }
}
