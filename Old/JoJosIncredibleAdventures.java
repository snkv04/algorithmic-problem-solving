import java.util.*;
import java.io.*;

public class JoJosIncredibleAdventures {
    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        for (int i = 1; i <= t; i++) {
            char[] string = br.readLine().toCharArray();
            char[] string2 = new char[string.length * 2];
            int n = string.length;
            for (int j = 0; j <= n-1; j++) {
                string2[j] = string[j];
                string2[j+n] = string[j];
            }

            int max1string = 0;
            int start = -1;
            int j = 0;
            for (j = 0; j <= 2 * n - 1; j++) {
                if (start==-1) {
                    if (string2[j]=='1') {
                        start = j;
                    }
                } else {
                    if (string2[j]=='0') {
                        max1string = Math.max(j-start, max1string);
                        start = -1;
                    }
                }
            }
            if (start!=-1) max1string = Math.max(j-start, max1string);

            if (max1string == 2 * n) {
                // string is all 1s
                long area = (long) n * n;
                pw.println(area);
            } else {
                if (max1string % 2 == 0) {
                    long area = ((long) (max1string / 2)) * ((max1string / 2) + 1);
                    pw.println(area);
                } else {
                    long area = max1string;
                    area = ((area + 1) / 2) * ((area + 1) / 2);
                    pw.println(area);
                }
            }
        }

        br.close(); pw.close();
    }
}
