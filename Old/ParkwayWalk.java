import java.util.*;
import java.io.*;

public class ParkwayWalk {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int m = Integer.parseInt(line[1]);
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int sum = 0;
            for (int i = 0; i <= n-1; i++) {
                sum += a[i];
            }
            pw.println(Math.max(sum-m, 0));
        }

        br.close(); pw.close();
    }
}
