import java.util.*;
import java.io.*;

public class TwinPermutations {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            for (int j = 0; j <= n-1; j++) {
                pw.print((n+1-a[j])+" ");
            }
            pw.println();
        }

        br.close(); pw.close();
    }
}
