import java.util.*;
import java.io.*;

public class Bakery {
    static long[] as;
    static long[] bs;
    static long[] cs;
    static int n;

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            br.readLine();
            String[] line = br.readLine().split(" ");
            n = Integer.parseInt(line[0]);
            long tc = Long.parseLong(line[1]);
            long tm = Long.parseLong(line[2]);

            as = new long[n];
            bs = new long[n];
            cs = new long[n];
            for (int j = 0; j <= n-1; j++) {
                line = br.readLine().split(" ");
                as[j] = Long.parseLong(line[0]);
                bs[j] = Long.parseLong(line[1]);
                cs[j] = Long.parseLong(line[2]);
            }
            
            long result = -1;
            for (long L = tc+tm; L>=0 && result==-1; L--) {
                long j = tc + tm - L;
                // the following loop checks through all combinations of tc and tm values
                // that sum up to L
                for (long k = 0; k <= j; k++) {
                    long tempTC = tc - k;
                    long tempTM = tm - j + k;
                    if (tempTC < 0 || tempTM < 0) continue;
                    // pw.print("L(line)="+L+", j="+j+", k="+k+", tempTC="+tempTC+", tempTM="+tempTM);
                    if (test(tempTC, tempTM)) {
                        result = j;
                    }
                    // pw.println();
                }
                // pw.println("========");
            }

            pw.println(result);
        }

        br.close(); pw.close();
    }

    static boolean test(long tempTC, long tempTM) {
        for (int i = 0; i <= n-1; i++) {
            if (as[i]*tempTC + bs[i]*tempTM > cs[i]) {
                return false;
            }
        }
        return true;
    }
}
