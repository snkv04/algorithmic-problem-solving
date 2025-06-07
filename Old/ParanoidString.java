import java.util.*;
import java.io.*;

public class ParanoidString {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            char[] S = br.readLine().toCharArray();
            long ans = n;
            for (int i = 1; i <= n-1; i++) {
                if (S[i]!=S[i-1]) ans += i;
            }
            pw.println(ans);
        }

        br.close(); pw.close();
    }
}
