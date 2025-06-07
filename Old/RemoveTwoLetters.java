import java.util.*;
import java.io.*;

public class RemoveTwoLetters {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            char[] s = br.readLine().toCharArray();
            int count = 0;
            for (int i = 2; i <= n-1; i++) {
                if (s[i]==s[i-2]) count++;
            }
            pw.println(n-1-count);
        }

        br.close(); pw.close();
    }
}
