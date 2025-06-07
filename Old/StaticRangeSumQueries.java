import java.util.*;
import java.io.*;

public class StaticRangeSumQueries {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int n = Integer.parseInt(line[0]);
        int q = Integer.parseInt(line[1]);
        int[] x = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        long[] prefsum = new long[n+1];
        for (int i = 0; i <= n-1; i++) { prefsum[i+1] = prefsum[i] + x[i]; }
        for (int i = 1; i <= q; i++) {
            line = br.readLine().split(" ");
            int a = Integer.parseInt(line[0]);
            int b = Integer.parseInt(line[1]);
            pw.println(prefsum[b]-prefsum[a-1]);
        }

        br.close(); pw.close();
    }
}
