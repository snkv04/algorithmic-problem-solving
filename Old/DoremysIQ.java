import java.util.*;
import java.io.*;

public class DoremysIQ {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            // String[] line = br.readLine().split(" ");
            // int n = Integer.parseInt(line[0]);
            // int q = Integer.parseInt(line[1]);
            // int[][] memo = new int[n+1][2];
            // int[][] qmemo = new int[n+1][2];
            // qmemo[0][0] = q; qmemo[0][1] = q;
            // for (int i = 1; i <= n; i++) {
            //     // choose to test
            //     int result1, result2;
            //     if (qmemo[i-1][0] == )
            //     memo[i][1] = 

            //     // choose to not test
            // }

            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int q = Integer.parseInt(line[1]);
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int iq = 0;
            char[] take = new char[n]; Arrays.fill(take, '0');
            for (int i = n-1; i >= 0; i--) {
                if (a[i] <= iq) {
                    take[i] = '1';
                } else {
                    if (iq < q) {
                        iq++;
                        take[i] = '1';
                    }
                }
            }
            for (char element : take) pw.print(element);
            pw.println();
        }

        br.close(); pw.close();
    }
}
