import java.util.*;
import java.io.*;

public class PoliceRecruits {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int police = 0;
        int ans = 0;
        for (int i = 0; i <= n-1; i++) {
            if (a[i] > 0) {
                police += a[i];
            } else {
                if (police == 0) ans++;
                else police--;
            }
        }
        pw.println(ans);

        br.close(); pw.close();
    }
}
