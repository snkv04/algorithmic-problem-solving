import java.util.*;
import java.io.*;

public class ABCSort {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            if (n<=2) {
                pw.println("YES");
                continue;
            }

            boolean works = true;
            int min = Integer.MAX_VALUE;
            for (int i = n-1; i >= 1; i-=2) {
                int currmax = Math.max(a[i], a[i-1]);
                int currmin = Math.min(a[i], a[i-1]);
                if (currmax > min) {
                    works = false;
                    break;
                } else {
                    min = currmin;
                }
            }
            if (n%2==1) {
                works = works && a[0]<=min;
            }
            pw.println(works?"YES":"NO");
        }

        br.close(); pw.close();
    }
}
