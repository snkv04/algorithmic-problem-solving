import java.util.*;
import java.io.*;

public class AceArbiter {
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
        int a = -1, b = -1;
        for (int i = 1; i <= n; i++) {
            int[] scores = Arrays.stream(br.readLine().split("-")).mapToInt(Integer::parseInt).toArray();
            int alice, bob;
            if (((scores[0]+scores[1]+1)/2) % 2 == 0) {
                alice = scores[0];
                bob = scores[1];
            } else {
                alice = scores[1];
                bob = scores[0];
            }

            if (i == 1) {
                a = alice;
                b = bob;
            }

            if (alice == 11 && bob == 11) {
                pw.println("error "+i);
                return;
            }
            
            if (alice - a < 0 || bob - b < 0) {
                pw.println("error "+i);
                return;
            }
            if ((alice == 11 && a == 11 && (bob - b > 0)) || (bob == 11 && b == 11 && (alice - a > 0))) {
                pw.println("error "+i);
                return;
            }
            a = alice;
            b = bob;
        }
        pw.println("ok");
    }
}