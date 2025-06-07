import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class GuessWho {
    static BufferedReader br;
    static PrintWriter pw;

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
        String[] s = br.readLine().split(" ");
        int n = Integer.parseInt(s[0]), m = Integer.parseInt(s[1]), q = Integer.parseInt(s[2]);
        String[] input = new String[n]; for (int i = 0; i < n; i++) input[i] = br.readLine();
        String[][] queries = new String[q][2]; for (int i = 0; i < q; i++) queries[i] = br.readLine().split(" ");

        TreeSet<Integer> possible = new TreeSet<>();
        for (int i = 0; i < n; i++) {
            boolean works = true;
            for (int j = 0; j < q; j++) {
                int attribute = Integer.parseInt(queries[j][0]);
                if (input[i].charAt(attribute-1) != queries[j][1].charAt(0)) {
                    works = false;
                    break;
                }
            }

            if (works) {
                possible.add(i+1);
            }
        }

        if (possible.size() > 1) {
            pw.println("ambiguous");
            pw.println(possible.size());
        } else {
            pw.println("unique");
            pw.println(possible.first());
        }
    }
}
