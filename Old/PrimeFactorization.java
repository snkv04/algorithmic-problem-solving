import java.util.*;
import java.io.*;

public class PrimeFactorization {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int n = Integer.parseInt(br.readLine());
        ArrayList<Integer> factors = new ArrayList<Integer>();
        for (int i = 2; i <= Math.sqrt(n); i++) {
            while (n % i == 0) {
                n /= i;
                factors.add(i);
            }
        }
        if (n != 1) {
            factors.add(n);
        }
        pw.print(factors.get(0));
        for (int i = 1; i <= factors.size()-1; i++) {
            pw.print("*" + factors.get(i));
        }

        br.close(); pw.close();
    }
}
