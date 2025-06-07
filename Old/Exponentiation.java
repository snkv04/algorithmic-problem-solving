import java.util.*;
import java.io.*;

public class Exponentiation {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        int modulus = (int) (1e9 + 7);
        for (int i = 1; i <= n; i++) {
            String[] line = br.readLine().split(" ");
            long a = Integer.parseInt(line[0]);
            long b = Integer.parseInt(line[1]);
            long result = 1;
            while (b != 0) {
                // // if b is odd and we decrement it, then it'll be even after, so we
                // // might as well just do the "if b is even" part every loop
                // if (b%2==0) {
                //     b /= 2;
                //     a *= a;
                //     a %= 1e9 + 7;
                // } else {
                //     result *= a;
                //     result %= 1e9 + 7;
                //     b--;
                // }
                if (b % 2 != 0) {
                    result *= a;
                    result %= modulus;
                    b--;
                }
                a *= a;
                a %= modulus;
                b /= 2;
            }
            pw.println(result);
        }

        br.close(); pw.close();
    }
}
