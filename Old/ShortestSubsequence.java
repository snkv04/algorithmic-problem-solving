import java.util.*;
import java.io.*;

public class ShortestSubsequence {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static int[] di = {0, 0, 1, -1}, dj = {1, -1, 0, 0};

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
        char[] s = br.readLine().toCharArray();
        TreeSet<Integer>[] positions = new TreeSet[4]; for (int i = 0; i <= 3; i++) positions[i] = new TreeSet<>();
        for (int i = 0; i <= s.length-1; i++) {
            if (s[i]=='A') positions[0].add(i);
            else if (s[i]=='C') positions[1].add(i);
            else if (s[i]=='G') positions[2].add(i);
            else positions[3].add(i);
        }

        int last = -1;
        ArrayList<Character> sequence = new ArrayList<>();
        boolean done = false;
        while (!done) {
            int next = -1;
            for (int i = 0; i <= 3; i++) {
                if (positions[i].higher(last) != null) {
                    next = Math.max(next, positions[i].higher(last));
                } else {
                    done = true;
                    sequence.add("ACGT".charAt(i));
                    break;
                }
            }
            if (!done) {
                sequence.add(s[next]);
                last = next;
            }
        }
        for (char c : sequence) pw.print(c);
    }
}
