import java.util.*;
import java.io.*;

public class YetAnotherMemeProblem {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int t = sc.nextInt();
        for (int i = 1; i <= t; i++) {
            int A = sc.nextInt();
            int B = sc.nextInt();
            int digits = (int) Math.log10(B)+1;
            long ans;
            if (B == (int)Math.pow(10,digits)-1) {
                ans = A * (long)digits;
            } else {
                ans = A * (long)(digits-1);
            }
            pw.println(ans);
        }

        sc.close(); pw.close();
    }
}
