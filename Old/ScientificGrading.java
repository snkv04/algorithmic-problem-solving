import java.util.*;
import java.io.*;

public class ScientificGrading {
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
        String[] s = br.readLine().split("e");
        
    }

    public class Num {
        long sign, sig, exp;

        public Num(long sign, long sig, long exp) {
            this.sign = sign;
            this.sig = sig;
            this.exp = exp;
        }
    }
}