import java.util.*;
import java.io.*;

public class YouBeTheJudge {
    static BufferedReader br;
    static PrintWriter pw;
    private static String horizontalTab = Character.toString((char) 9);
    private static String verticalTab = Character.toString((char) 11);

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);
        int t = 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        ArrayList<String> nums = new ArrayList<>();
        String line;
        while ((line = br.readLine()) != null) {
            String[] split = line.split(" ");
            for (String s : split) {
                String[] split2 = s.split(horizontalTab);
                for (String s2 : split2) {
                    String[] split3 = s2.split(verticalTab);
                    for (String s3 : split3) {
                        if (s3.length() > 0) {
                            nums.add(s3);
                        }
                    }
                }
            }
        }

        if (nums.size() != 3) {
            pw.println(0);
            return;
        }
        for (int i = 0; i <= 2; i++) {
            String num = nums.get(i);
            if (num.charAt(0)=='+' || num.charAt(0)=='-' || num.charAt(0)=='0') {
                pw.println(0);
                return;
            }
        }

        int sum = -1;
        try {
            sum = Integer.parseInt(nums.get(0));
        } catch (Exception e) {
            pw.println(0);
            return;
        }

        int a = -1;
        try {
            a = Integer.parseInt(nums.get(1));
        } catch (Exception e) {
            pw.println(0);
            return;
        }

        int b = -1;
        try {
            b = Integer.parseInt(nums.get(2));
        } catch (Exception e) {
            pw.println(0);
            return;
        }

        ArrayList<Integer> aFactors = primeFactorization(a), bFactors = primeFactorization(b);
        if (sum <= 3 || sum > (int)1e9 || sum % 2 == 1 || aFactors.size()!=1 || bFactors.size()!=1 || a < 2 || b < 2) {
            pw.println(0);
        } else {
            pw.println(sum==a+b?1:0);
        }
    }
    
    static ArrayList<Integer> primeFactorization(int n) {
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
        return factors;
    }
}
