import java.util.*;
import java.io.*;

public class TernaryXOR {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            char[] x = br.readLine().toCharArray();
            char[] a = new char[n], b = new char[n];
            a[0] = '1'; b[0] = '1';
            int move = 0;
            for (int i = 1; i <= n-1; i++) {
                if (x[i]=='2') {
                    if (move==0) {
                        a[i] = '1';
                        b[i] = '1';
                    } else {
                        b[i] = '2';
                        a[i] = '0';
                    }
                } else if (x[i]=='1') {
                    if (move==0) {
                        a[i] = '1';
                        move=1;
                        b[i] = '0';
                    } else {
                        b[i]='1';
                        a[i] = '0';
                    }
                } else {
                    a[i]='0';
                    b[i]='0';
                }
            }
            pw.println(a);
            pw.println(b);
        }

        br.close(); pw.close();
    }
}
