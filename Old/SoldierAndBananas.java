import java.util.*;
import java.io.*;

public class SoldierAndBananas {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int k = sc.nextInt();
        int n = sc.nextInt();
        int w = sc.nextInt();
        long ans = 0;
        for (long i = 1; i <= w; i++) {
            ans += i * k;
        }
        pw.print(Math.max(0, ans-n));

        sc.close(); pw.close();
    }
}
