import java.util.*;
import java.io.*;

public class BeatTheOdds {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        while (t-->0) {
            int n = sc.nextInt();
            int even = 0, odd = 0;
            for (int i = 1; i <= n; i++) {
                if (sc.nextInt() % 2 == 0) even++;
                else odd++;
            }
            pw.println(Math.min(even, odd));
        }


        sc.close(); pw.close();
    }
}
