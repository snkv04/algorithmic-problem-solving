import java.util.*;
import java.io.*;

public class CoffeeCupCombo {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);
        
        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    public static void solve() throws IOException {
        int n = Integer.parseInt(br.readLine());
        char[] c = br.readLine().toCharArray();
        char[] c2 = new char[n];
        for (int i = 0; i < n; i++) {
            if (c[i] == '1') {
                for (int j = i; j <= Math.min(n-1, i+2); j++) {
                    c2[j] = '1';
                }
            }
        }

        int count =0 ;
        for (int i =0 ; i < n; i++) {
            if (c2[i] == '1') count++;
        }
        pw.println(count);
    }
}