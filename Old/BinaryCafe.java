import java.util.*;
import java.io.*;

public class BinaryCafe {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int k = Integer.parseInt(line[1]);
            int exp = 1;
            for (int i = 1; i <= k && exp <= n; i++) {
                exp *= 2;
            }
            pw.println(Math.min(exp, n+1));
        }

        br.close(); pw.close();
    }
}
