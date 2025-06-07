import java.util.*;
import java.io.*;

public class KeepItBeautiful {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for ( ; t-->0; ) {
            int q = Integer.parseInt(br.readLine());
            int[] x = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            
            int original = x[0], last = original;
            pw.print(1);
            int changes = 0;
            for (int i = 1; i <= q-1; i++) {
                if (changes == 0) {
                    if (x[i] >= last) {
                        pw.print(1);
                        last = x[i];
                    } else {
                        if (x[i] <= original) {
                            pw.print(1);
                            last = x[i];
                            changes++;
                        } else {
                            pw.print(0);
                        }
                    }
                } else {
                    if (x[i] >= last && x[i] <= original) {
                        pw.print(1);
                        last = x[i];
                    } else {
                        pw.print(0);
                    }
                }
            }
            pw.println();
        }

        br.close(); pw.close();
    }
}
