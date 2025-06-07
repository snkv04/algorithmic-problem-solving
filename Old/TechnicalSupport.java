import java.util.*;
import java.io.*;

public class TechnicalSupport {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i=1; i<=t; i++) {
            int n = Integer.parseInt(br.readLine());
            char[] dialog = br.readLine().toCharArray();
            int count = 0;
            for (int j = 0; j <= n-1; j++) {
                if (dialog[j] == 'Q') count++;
                else count = Math.max(0, count-1);
            }

            if (count == 0) pw.println("Yes");
            else pw.println("No");
        }

        br.close(); pw.close();
    }
}
