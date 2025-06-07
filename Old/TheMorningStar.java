import java.util.*;
import java.io.*;

public class TheMorningStar {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        int t = Integer.parseInt(br.readLine());
        while (t-->0) {
            int n = Integer.parseInt(br.readLine());
            Multiset vertical = new Multiset(), horizontal = new Multiset(),
                upright = new Multiset(), downright = new Multiset();
            long ans = 0;
            while (n-->0) {
                String[] line = br.readLine().split(" ");
                int x = Integer.parseInt(line[0]);
                int y = Integer.parseInt(line[1]);
                int ud = x;
                int lr = y;
                int ur = x-y;
                int dr = x+y;
                if (vertical.mset.containsKey(ud)) {
                    ans += vertical.mset.get(ud);
                }
                if (horizontal.mset.containsKey(lr)) {
                    ans += horizontal.mset.get(lr);
                }
                if (upright.mset.containsKey(ur)) {
                    ans += upright.mset.get(ur);
                }
                if (downright.mset.containsKey(dr)) {
                    ans += downright.mset.get(dr);
                }
                vertical.add(ud);
                horizontal.add(lr);
                upright.add(ur);
                downright.add(dr);
            }
            pw.println(2*ans);
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
