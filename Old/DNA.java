import java.util.*;
import java.io.*;

public class DNA {
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
        char[] dna = br.readLine().toCharArray();
        int n = dna.length;
        int[] a = new int[n+1], t = new int[n+1], g = new int[n+1], c = new int[n+1];
        for (int i = 1; i <= n; i++) {
            a[i] = a[i-1] + ((dna[i-1] == 'A') ? 1 : 0);
            t[i] = t[i-1] + ((dna[i-1] == 'T') ? 1 : 0);
            g[i] = g[i-1] + ((dna[i-1] == 'G') ? 1 : 0);
            c[i] = c[i-1] + ((dna[i-1] == 'C') ? 1 : 0);
        }

        int m = Integer.parseInt(br.readLine());
        while (m-->0) {
            String[] split = br.readLine().split(" ");
            int l = Integer.parseInt(split[0]), r = Integer.parseInt(split[1]);
            int cntA = a[r]-a[l-1];
            int cntT = t[r]-t[l-1];
            int cntG = g[r]-g[l-1];
            int cntC = c[r]-c[l-1];
            TreeSet<Integer> sorted = new TreeSet<Integer>();
            sorted.add(cntA); sorted.add(cntT); sorted.add(cntG); sorted.add(cntC);

            while (!sorted.isEmpty()) {
                int count = sorted.pollLast();
                if (cntA == count) {
                    pw.print('A');
                }
                if (cntT == count) {
                    pw.print('T');
                }
                if (cntG == count) {
                    pw.print('G');
                }
                if (cntC == count) {
                    pw.print('C');
                }
            }
            pw.println();
        }
    }
}