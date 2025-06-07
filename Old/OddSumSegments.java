import java.util.*;
import java.io.*;

public class OddSumSegments {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int q = Integer.parseInt(br.readLine());
        for (int i=1; i<=q; i++) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int k = Integer.parseInt(line[1]);
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int[] r = new int[k];
            int kit = 1;
            int j;
            for (j = 0; j<=n-1 && kit <= k-1; j++) {
                if (a[j]%2==1) {
                    r[kit-1] = j+1;
                    kit++;
                }
            }
            if (j==n) {
                pw.println("NO");
            } else {
                // kit now equals k
                int numOdd = 0;
                for ( ; j <= n-1; j++) {
                    if (a[j] % 2 == 1) numOdd++;
                }
                if (numOdd % 2 == 1) {
                    r[k-1] = n;
                    pw.println("YES");
                    for (int b = 0; b <= k-1; b++) {
                        pw.print(r[b] + " ");
                    }
                    pw.println();
                } else {
                    pw.println("NO");
                }
            }
        }

        br.close(); pw.close();
    }
}
