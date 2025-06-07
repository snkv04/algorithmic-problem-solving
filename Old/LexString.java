import java.util.*;
import java.io.*;

public class LexString {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            String[] line = br.readLine().split(" ");
            int n = Integer.parseInt(line[0]);
            int m = Integer.parseInt(line[1]);
            int k = Integer.parseInt(line[2]);
            char[] a = br.readLine().toCharArray();
            char[] b = br.readLine().toCharArray();
            Arrays.sort(a); Arrays.sort(b);

            int i = 0, j = 0;
            int same = 0;
            while (i < n && j < m) {
                if (Math.abs(same)==k) {
                    if (same < 0) {
                        same = 1;
                        pw.print(b[j]);
                        j++;
                    } else {
                        same = -1;
                        pw.print(a[i]);
                        i++;
                    }
                } else {
                    if (a[i] < b[j]) {
                        pw.print(a[i]);
                        if (same <= 0) same--;
                        else same = -1;
                        i++;
                    } else {
                        pw.print(b[j]);
                        if (same >= 0) same++;
                        else same = 1;
                        j++;
                    }
                }
            }
            pw.println();
        }

        br.close(); pw.close();
    }
}
