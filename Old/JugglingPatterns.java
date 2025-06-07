import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class JugglingPatterns {
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
        String line;
        while ((line = br.readLine()) != null) {
            char[] arr = line.toCharArray();
            int n = arr.length;
            int sum = 0;
            for (int i = 0; i <= n-1; i++) {
                sum += arr[i]-'0';
            }
            if (sum % n != 0) {
                pw.println(line+": invalid # of balls");
                continue;
            }

            int balls = sum / n;
            int[] newArr = new int[900]; for (int i = 0; i < 900; i++) newArr[i] = arr[i%n];
            boolean[] visited = new boolean[900];
            boolean works = true;
            for (int i = 0; i + newArr[i] < 900; i++) {
                if (visited[i+newArr[i]]) {
                    works = false;
                    break;
                }
                visited[i+newArr[i]] = true;
            }
            pw.println(line+": "+(works?("valid with "+balls+" balls"):"invalid pattern"));
        }
    }
}
