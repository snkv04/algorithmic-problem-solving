import java.util.*;
import java.io.*;

public class NtarsisSet {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int tc = Integer.parseInt(br.readLine());
        while (tc-- > 0) {
            int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            int n = a[0];
            int k = a[1];
            a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            if (a[0] > 1) { pw.println(1); continue; } // don't need to waste time
            for (int i = 0; i <= n-1; i++) {
                a[i] -= i+1;
            }
            // pw.println(Arrays.toString(a));

            long position = 1;
            int adding = -1;
            for (int i = 1; i <= k; i++) {
                while (adding+1 <= n-1 && a[adding+1] < position) {
                    adding++;
                }
                position += adding+1;
            }
            pw.println(position);
        }

        br.close(); pw.close();
    }
}
