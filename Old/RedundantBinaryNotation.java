import java.util.*;
import java.io.*;

public class RedundantBinaryNotation {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = 998244353;
    static HashMap<Pair, Integer> memo = new HashMap<>();
    static long t;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        solve();

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        String[] asdf = br.readLine().split(" ");
        long n = Long.parseLong(asdf[0]);
        t = Integer.parseInt(asdf[1]);
        pw.println(count(n, 54));
    }

    static int count(long num, int digit) {
        // pw.println("digit="+digit+", t="+t+", and upper bound is "+(t * (((long)1 << (digit+1))-1)));
        if (num < 0 || num > t * (((long)1 << (digit+1))-1) ) {
            // pw.println("here");
            return 0;
        }
        if (memo.containsKey(new Pair(num, digit))) return memo.get(new Pair(num, digit));
        if (digit == 0) return 1;

        int val = 0;
        for (int i = 0; i <= t; i++) {
            val += count(num - i*((long)1<<digit), digit-1);
            val %= MOD;
        }
        memo.put(new Pair(num, digit), val);
        return val;
    }

    static class Pair {
        long num;
        int digit;

        public Pair(long num, int digit) {
            this.num = num;
            this.digit = digit;
        }

        @Override
        public boolean equals(Object obj) {
            Pair other = (Pair) obj;
            return this.num==other.num && this.digit==other.digit;
        }

        @Override
        public int hashCode() {
            return (this.num+" "+this.digit).hashCode();
        }
    }
}
