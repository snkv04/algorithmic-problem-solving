import java.util.*;
import java.io.*;

public class EthingEwhereAllButOne {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            double sum = 0;
            for (int i = 0; i <= n-1; i++) {
                sum += a[i];
            }
            boolean works = false;
            for (int i = 0; i <= n-1; i++){
                if ((sum - a[i]) / (n-1) == a[i]) {
                    works = true;
                    break;
                }
            }
            pw.println(works?"YES":"NO");
        }

        br.close(); pw.close();
    }
}
