import java.util.*;
import java.io.*;

/**
 * @author Sri Vangaru
 */
public class Incognito {
    static BufferedReader br;
    static PrintWriter pw;

    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine()); // 1;
        while (t-->0) {
            solve();
        }

        br.close(); pw.close();
    }

    static void solve() throws IOException {
        int n = Integer.parseInt(br.readLine());
        if (n==0) {pw.println(0);return;}
        Multiset ms = new Multiset();
        while (n-->0) {
            String[] split = br.readLine().split(" ");
            ms.add(split[1]);
        }
        int ans = 1;
        for (Map.Entry<String, Integer> entry : ms.mset.entrySet()) {
            ans *= entry.getValue() + 1;
        }
        pw.println(ans-1);
    }

    static class Multiset { // ordered multiset
        TreeMap<String, Integer> mset = new TreeMap<>();

        public void add(String x) {
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + 1);
            } else {
                mset.put(x, 1);
            }
        }
        
        public void remove(String x) {
            mset.put(x, mset.get(x) - 1);
            if (mset.get(x) == 0) mset.remove(x);
        }
    }
}
