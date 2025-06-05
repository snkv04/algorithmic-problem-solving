// THIS SOLUTION GIVES THE CORRECT ANSWER

import java.util.*;
import java.io.*;

public class BracketPairing2 {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static long ans;
    static char[] s; static int n;
    static HashSet<Character> opens = new HashSet<>(), closes = new HashSet<>();
    static HashMap<Character, Character> closeToOpen;
    static HashMap<String, Long> memo;

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
        s = br.readLine().toCharArray();
        n = s.length;
        ans = 0;
        char[] possibilities = "()[]{}<>".toCharArray();
        closeToOpen = new HashMap<>();
        for (int i = 0; i <= 7; i++) {
            if (i%2==0) opens.add(possibilities[i]);
            else {
                closes.add(possibilities[i]);
                closeToOpen.put(possibilities[i], possibilities[i-1]);
            }
        }
        // pw.println(opens);
        // pw.println(closes);
        // pw.println(closeToOpen);

        memo = new HashMap<>();
        if (s[0] == '?') {
            for (char start : opens) {
                ans += build(String.valueOf(start), 0);
            }
        } else {
            if (closes.contains(s[0])) {
                pw.println(0);
                return;
            }
            ans += build(String.valueOf(s[0]), 0);
        }
        // for (Map.Entry<String, Long> entry : memo.entrySet()) pw.println("key: "+entry.getKey()+"\nval: "+entry.getValue());
        // pw.println(memo.containsKey("< ( 1"));
        pw.println(ans);
    }

    static long build(String soFar, int index) {
        Stack<Character> pairs = new Stack<>();
        char[] arr = soFar.toCharArray();
        for (char c : arr) {
            if (opens.contains(c)) {
                pairs.add(c);
            }
            if (closes.contains(c)) {
                pairs.pop();
            }
        }
        if (index==n-1) {
            // pw.println("at end of string");
            if (pairs.isEmpty()) {
                // pw.println("good");
                return 1;
            }
            else return 0;
        }

        int canClose = 0;
        for (int i = index+1; i <= n-1; i++) {
            if (closes.contains(s[i]) || s[i] == '?') canClose++;
        }
        if (canClose < pairs.size()) return 0;

        char lastOpen = pairs.isEmpty() ? 'a' : pairs.peek(); // saving for later use
        String id = "";
        while (!pairs.isEmpty()) id += pairs.pop();
        id += index;
        if (memo.containsKey(id)) {
            // pw.println("has");
            return memo.get(id);
        }

        long val = 0;
        if (s[index+1] == '?') {
            for (char opener : opens) {
                // pw.println("1");
                val += build(soFar+opener, index+1);
            }
            for (char closer : closes) {
                if (lastOpen == closeToOpen.get(closer)) {
                    // pw.println("2");
                    val += build(soFar+closer, index+1);
                }
            }
        } else {
            if (opens.contains(s[index+1])) {
                // pw.println("3");
                val = build(soFar + s[index+1], index+1);
            } else {
                if (closeToOpen.get(s[index+1]) != lastOpen) {
                    // pw.println("4");
                    val = 0;
                } else {
                    // pw.println("5");
                    val = build(soFar+s[index+1], index+1);
                }
            }
        }
        memo.put(id, val);
        return val;
    }

    static class Pair {
        int a, b;

        public Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }
        
        @Override
        public boolean equals(Object obj) {
            if (this == obj) return true;
            if (obj == null) return false;
            if (!(obj instanceof Pair)) return false;

            Pair other = (Pair) obj;
            return this.a == other.a && this.b == other.b;
        }

        @Override
        public int hashCode() {
            return (this.a+" "+this.b).hashCode();
        }
    }
}
