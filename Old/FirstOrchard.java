import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class FirstOrchard {
    static BufferedReader br;
    static PrintWriter pw;
    static int MOD = (int) (1e9 + 7); // 998244353;
    static int[] di = {0, 0, 1, -1}, dj = {1, -1, 0, 0};
    static HashMap<String, Double> mem;

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
        int[] a = Arrays.stream(br.readLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int r = a[0], g = a[1], b = a[2], y = a[3], s = a[4];
        mem = new HashMap<String, Double>();
        pw.println(solve2(new int[] {r, g, b, y}, s));
    }

    static double solve2(int[] rgby, int s) {
        if (s == 0) {
            return 0;
        }

        int sum = 0;
        for (int i = 0; i <= 3; i++) sum += rgby[i];
        if (sum == 0) {
            return 1;
        }

        String key = Arrays.toString(rgby) + " " + s;
        if (mem.containsKey(key)) {
            return mem.get(key);
        }

        int available = 2; // for fruits and raven
        for (int i = 0; i <= 3; i++) {
            if (rgby[i] > 0) available++;
        }

        double ans = 0;
        for (int i = 0; i <= 3; i++) {
            if (rgby[i] > 0) {
                int[] newArr = rgby.clone();
                newArr[i]--;
                ans += (1.0 / available) * solve2(newArr, s);
            }
        }
        ans += (1.0 / available) * solve2(rgby.clone(), s-1);

        int max = 0; for (int i = 0; i <= 3; i++) max = Math.max(max, rgby[i]);
        int count = 0; for (int i = 0; i <= 3; i++) if (rgby[i] == max) count++;
        for (int i = 0; i <= 3; i++) {
            if (rgby[i] == max) {
                int[] newArr = rgby.clone();
                newArr[i]--;
                ans += (1.0 / (available * count)) * solve2(newArr, s);
            }
        }

        mem.put(key, ans);
        return ans;
    }
}
