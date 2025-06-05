import java.util.*;
import java.io.*;

public class BearAndBigBrother {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int a = sc.nextInt();
        int b = sc.nextInt();
        int ans = 0;
        while (a <= b) {
            a*=3;
            b*=2;
            ans++;
        }
        pw.println(ans);

        sc.close(); pw.close();
    }
}
