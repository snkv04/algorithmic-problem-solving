import java.util.*;
import java.io.*;

public class Astrophysicists {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        for (int i = 1; i <=t; i++) {
            long n = sc.nextInt();
            long k = sc.nextInt();
            long g = sc.nextInt();
            long max = g/2; if (g%2==0)max--;
            long saved = max*(n-1);
            long coins = k*g;
            coins -= max*(n-1);
            if (coins<=0) {
                pw.println(k*g);
                continue;
            }

            if (coins%g <= max) saved += coins%g;
            else saved -= g - (coins%g);
            pw.println(saved);
        }

        sc.close(); pw.close();
    }
}
