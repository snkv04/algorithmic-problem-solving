import java.util.*;
import java.io.*;

public class Showstopper {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt((br.readLine()));
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt((br.readLine()));
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt((Integer::parseInt)).toArray();
            int[] b = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            if (n == 1) {
                pw.println("yes");
                continue;
            }
            
            // for each index, put all the maxs in a and all the mins in b
            // then check the condition for both a and b
            for (int j = 0; j <= n-1; j++) {
                if (a[j] < b[j]) {
                    int temp = a[j];
                    a[j] = b[j];
                    b[j] = temp;
                }
            }
            int maxA = Integer.MIN_VALUE;
            int maxB = Integer.MIN_VALUE;
            for (int j = 0; j <=n-2; j++) {
                maxA = Math.max(maxA, a[j]);
                maxB = Math.max(maxB, b[j]);
            }
            if (maxA <= a[n-1] && maxB <= b[n-1]) pw.println("yes");
            else pw.println("no");
        }

        br.close(); pw.close();
    }
}
