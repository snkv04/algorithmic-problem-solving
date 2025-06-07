import java.util.*;
import java.io.*;

public class XORSpeciaLISt {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            if (n%2==0) {
                pw.println("YES");
                continue;
            }

            boolean works = false;
            for (int i = 0; i <= n-2; i++) {
                if (a[i]>=a[i+1]) {
                    works = true;
                    break;
                }
            }
            pw.println(works?"YES":"NO");
        }

        br.close(); pw.close();
    }
}
