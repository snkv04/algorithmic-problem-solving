import java.util.*;
import java.io.*;

public class LuoTianyiTable {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int m = Integer.parseInt(line[1]);
            int[] b = Arrays.stream(br.readLine().split(" ")).mapToInt((Integer::parseInt)).toArray();
            Arrays.sort(b);
            int maxDiff = b[(n*m)-1] - b[0];
            int maxDiff2 = Math.max(b[(n*m)-1]-b[1], b[(n*m)-2]-b[0]);
            long sum = 0 + (Math.min(n,m) * (Math.max(n,m)-1) * (long)maxDiff) + ((Math.min(n,m)-1)* (long)maxDiff2);
            pw.println(sum);
        }

        br.close(); pw.close();
    }
}
