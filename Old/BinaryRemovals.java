import java.util.*;
import java.io.*;

public class BinaryRemovals {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            char[] s = br.readLine().toCharArray();
            if (s.length <= 3) {
                pw.println("YES");
                continue;
            }

            boolean works = true;
            boolean checking = false;
            for (int i = 0; i <= s.length-4; i++) {
                if (s[i]=='1'&&s[i+1]=='1'&&s[i+2]=='0'&&s[i+3]=='0') {
                    works = false;
                    break;
                }
            }
            pw.println(works?"YES":"NO");
        }

        br.close(); pw.close();
    }

    // // // //

    static class Multiset {
        TreeMap<Integer, Integer> mset = new TreeMap<>();

        public void add(int x) {
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + 1);
            } else {
                mset.put(x, 1);
            }
        }
        
        public void remove(int x) {
            mset.put(x, mset.get(x) - 1);
            if (mset.get(x) == 0) mset.remove(x);
        }

        public void add(int x, int q) {
            // q for quantity
            if (mset.containsKey(x)) {
                mset.put(x, mset.get(x) + q);
            } else {
                mset.put(x, q);
            }
        }
    }
}
