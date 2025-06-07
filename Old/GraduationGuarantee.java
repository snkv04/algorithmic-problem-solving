import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class GraduationGuarantee {
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
        String[] s = br.readLine().split(" ");
        int n = Integer.parseInt(s[0]), k = Integer.parseInt(s[1]);
        double[] probs = Arrays.stream(br.readLine().split(" ")).mapToDouble(Double::parseDouble).toArray();
        Arrays.sort(probs);
        for (int i = 0; i < n/2; i++) {
            double temp = probs[i];
            probs[i] = probs[n-1-i];
            probs[n-1-i] = temp;
        }

        double[][] mem = new double[n+1][n+1];
        mem[0][0] = 1;
        for (int solved = 1; solved <= n; solved++) {
            double prob = probs[solved-1];
            for (int correct = 0; correct <= solved; correct++) {
                mem[solved][correct] = (1-prob) * mem[solved-1][correct];
                if (correct-1 >= 0) mem[solved][correct] += prob * mem[solved-1][correct-1];
            }
        }

        double ans = 0;
        for (int i = k; i <= n; i++) {
            int needCorrect = (i+k+1)/2;
            double sum = 0;
            for (int j = needCorrect; j <= n; j++) {
                sum += mem[i][j];
            }
            ans = Math.max(ans, sum);
        }
        pw.println(ans);
    }
}
