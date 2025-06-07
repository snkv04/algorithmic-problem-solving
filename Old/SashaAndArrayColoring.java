import java.util.*;
import java.io.*;

public class SashaAndArrayColoring {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            Arrays.sort(a);
            int ans = 0;
            for (int j = 0; j <= (n/2)-1; j++) {
                ans += a[n-1-j] - a[j];
            }
            pw.println(ans);
        }

        br.close(); pw.close();
    }
}
