import java.util.*;
import java.io.*;

public class PeaPattern {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {

        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        solve();

        br.close();
        pw.close();
    }

    public static void solve() throws IOException {
        String[] s = br.readLine().split(" ");
        String n = s[0], m = s[1];
        if (m.equals(n)) {
            pw.println(1);
            return;
        }

        HashSet<String> set = new HashSet<>();
        set.add(n);
        for (int i = 2; i <= 100; i++) {
            n = next(n);
            if (m.equals(n)) {
                pw.println(i);
                return;
            } else if (set.contains(n)) {
                pw.println("Does not appear");
                return;
            }
            set.add(n);
        }
        pw.println("I'm bored");
    }

    static String next(String oldStr) {
        int n = oldStr.length();
        TreeMap<Character, Integer> map = new TreeMap<>();
        for (int i = 0; i < n; i++) {
            char c = oldStr.charAt(i);
            if (map.containsKey(c)) {
                map.put(c, map.get(c) + 1);
            } else {
                map.put(c, 1);
            }
        }

        StringBuilder sb = new StringBuilder();
        for (Map.Entry<Character, Integer> entry : map.entrySet()) {
            sb.append(entry.getValue());
            sb.append(entry.getKey());
        }
        return sb.toString();
    }
}