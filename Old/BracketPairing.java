// THIS SOLUTION GIVES THE WRONG ANSWER

import java.util.*;
import java.io.*;

public class BracketPairing {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static long ans;
    static char[] s; static int n;
    static HashSet<Character> opens = new HashSet<>(), closes = new HashSet<>();
    static HashMap<Character, Character> closeToOpen, openToClose;
    static HashMap<Counts, Long> leftOpen = new HashMap<>(), rightClose = new HashMap<>();

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
        closeToOpen = new HashMap<>(); openToClose = new HashMap<>();
        for (int i = 0; i <= 7; i++) {
            if (i%2==0) opens.add(possibilities[i]);
            else {
                closes.add(possibilities[i]);
                closeToOpen.put(possibilities[i], possibilities[i-1]);
                openToClose.put(possibilities[i-1], possibilities[i]);
            }
        }
        // pw.println(opens);
        // pw.println(closes);
        // pw.println(closeToOpen);

        if (s[0] == '?') {
            for (char start : opens) {
                build(String.valueOf(start), 0, "left");
            }
        } else {
            if (closes.contains(s[0])) {
                pw.println(0);
                return;
            }
            build(String.valueOf(s[0]), 0, "left");
        }

        if (s[n-1] == '?') {
            for (char end : closes) {
                build(String.valueOf(end), n-1, "right");
            }
        } else {
            if (opens.contains(s[n-1])) {
                pw.println(0);
                return;
            }
            build(String.valueOf(s[n-1]), n-1, "right");
        }

        for (Map.Entry<Counts, Long> entry : leftOpen.entrySet()) {
            if (rightClose.containsKey(entry.getKey())) {
                ans += entry.getValue() * rightClose.get(entry.getKey());
            }
        }
        pw.println(ans);
    }

    static void build(String soFar, int index, String side) {
        HashSet<Character> unlimited, restricted;
        HashMap<Character, Character> matcher;
        int direction;
        if (side.equals("left")) {
            unlimited = opens;
            restricted = closes;
            matcher = closeToOpen;
            direction = 1;
        } else {
            unlimited = closes;
            restricted = opens;
            matcher = openToClose;
            direction = -1;
        }

        Stack<Character> pairs = new Stack<>();
        char[] arr = soFar.toCharArray();
        for (char c : arr) {
            if (unlimited.contains(c)) {
                pairs.add(c);
            }
            if (restricted.contains(c)) {
                pairs.pop();
            }
        }
        if (index == n/2-1 && side.equals("left")) {
            int round =0 , square = 0, curly = 0, angle = 0;
            while (!pairs.isEmpty()) {
                char bracket = pairs.pop();
                if (bracket=='(')round++;
                if (bracket=='[')square++;
                if (bracket=='{')curly++;
                if (angle=='<')angle++;
            }
            Counts c = new Counts(round, square, curly, angle);
            if (leftOpen.containsKey(c)) leftOpen.put(c, leftOpen.get(c)+1);
            else leftOpen.put(c, (long)1);
            return;
        }
        if (index==n/2 && side.equals("right")) {
            int round = 0, square = 0, curly = 0, angle = 0;
            while (!pairs.isEmpty()) {
                char bracket = pairs.pop();
                if (bracket==')')round++;
                if (bracket==']')square++;
                if (bracket=='}')curly++;
                if (angle=='>')angle++;
            }
            Counts c = new Counts(round, square, curly, angle);
            if (rightClose.containsKey(c)) rightClose.put(c, rightClose.get(c)+1);
            else rightClose.put(c, (long)1);
            return;
        }

        char lastGood = pairs.isEmpty() ? 'a' : pairs.peek(); // saving for later use
        if (s[index+direction] == '?') {
            for (char c : unlimited) {
                build(soFar+c, index+direction, side);
            }
            for (char c : restricted) {
                if (!pairs.isEmpty() && lastGood == matcher.get(c)) {
                    build(soFar+c, index+direction, side);
                }
            }
        } else {
            if (unlimited.contains(s[index+direction])) {
                build(soFar + s[index+direction], index+direction, side);
            } else {
                if (pairs.isEmpty() || matcher.get(s[index+direction]) != lastGood) {
                    return;
                } else {
                    build(soFar+s[index+direction], index+direction, side);
                }
            }
        }
    }

    static class Counts {
        int round, square, curly, angle;

        public Counts(int round, int square, int curly, int angle) {
            this.round = round;
            this.square = square;
            this.curly = curly;
            this.angle = angle;
        }

        @Override
        public boolean equals(Object obj) {
            Counts other = (Counts)obj;
            return this.round==other.round && this.square==other.square && this.curly==other.curly && this.angle==other.angle;
        }

        @Override
        public int hashCode() {
            return (this.round+" "+this.square+" "+this.curly+" "+this.angle).hashCode();
        }
    }
}
