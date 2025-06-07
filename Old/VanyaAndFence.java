import java.util.*;
import java.io.*;

public class VanyaAndFence {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(System.in);
        PrintWriter pw = new PrintWriter(System.out);

        int n = sc.nextInt();
        int h = sc.nextInt();
        int ans = 0;
        for (int i = 0; i <= n-1; i++) {
            if (sc.nextInt() > h) {
                ans++;
            }
            ans++;
        }
        pw.print(ans);

        sc.close(); pw.close();
    }
}
