import java.util.*;
import java.io.*;

public class ChallengeKattis4 {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;

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
        int n = s.length;
        ArrayList<Integer>[] adj = new ArrayList[n], adj2 = new ArrayList[n];
        for (int i = 0; i < n; i++) { adj[i] = new ArrayList<>(); adj2[i] = new ArrayList<>(); }
        for (int i = 0; i <= n-1; i++) {
            for (int j = i+1; j <= n-1; j++) {
                if (s[i] < s[j]) {
                    adj[i].add(j);
                    adj2[j].add(i);
                }
            }
        }

        int[] memo = new int[n], memo2 = new int[n];
        for (int i = n-1; i >= 0; i--) {
            int max = 0;
            for (int next : adj[i]) {
                max = Math.max(max, memo[next]);
            }
            memo[i] = 1 + max;
        }
        for (int i = 0; i <= n-1; i++) {
            int max = 0;
            for (int next : adj2[i]) {
                max = Math.max(max, memo2[next]);
            }
            memo2[i] = 1 + max;
        }

        int best = 0;
        for (int i = 0; i <= n-1; i++) {
            best = Math.max(best, memo[i] + memo2[i] - 1);
        }
        pw.println(26-best);
    }
}
