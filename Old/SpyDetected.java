import java.util.*;
import java.io.*;

public class SpyDetected {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            if (a[0]!=a[1] && a[1]==a[2]) {
                pw.println(1);
                continue;
            } else if (a[0]!=a[1] && a[0]==a[2]) {
                pw.println(2); continue;
            } else if (a[0]==a[1] && a[1]!=a[2]) {
                pw.println(3); continue;
            }

            int regular = a[0];
            for (int j = 3; j <= n-1; j++) {
                if (a[j] != regular) {
                    pw.println(j+1);
                    break;
                }
            }
        }

        br.close(); pw.close();
    }
}
